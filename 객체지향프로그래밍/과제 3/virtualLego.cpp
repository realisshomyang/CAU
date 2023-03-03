////////////////////////////////////////////////////////////////////////////////
//
// File: virtualLego.cpp
//
// Original Author: 박창현 Chang-hyeon Park, 
// Modified by Bong-Soo Sohn and Dong-Jun Kim
// 
// Originally programmed for Virtual LEGO. 
// Modified later to program for Virtual Billiard.
//        
////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>

IDirect3DDevice9* Device = NULL;

// window size
const int Width  = 1024;
const int Height = 768;
//INITIAL STATE OR NOT(DID SHOOT THE BALL? FLAG)
bool shootflag = false;
bool flag = false;
// 46 YELLOW BALLS
// initialize the position (coordinate) of each ball (ball0 ~ ball3)
const float spherePos[46][2] = { {-1.3f , -1.0f} , {-1.3f , -1.5f},{0, 0.5f} , {1.3f, -1.0f}, {1.3f, -1.5f}, {2.3f, 0}, {2.3f, -0.6f}, {2.3f, -1.2f}, {2.3f, -1.8f}, {2.3f, -2.4f}, {2.3f, -3.0f}, {2.3f,1.3f},{2.1f , -3.5f},{1.6f, -3.5f},{1.1f, -3.5f},{ 0.6f, -3.5f }, {0.1f,-3.5f},{-0.4f,-3.5f},{-0.9f, -3.5f}, {-1.4f,-3.5f
},{-1.9f, -3.5f}, {-2.1f,-2.7f},{-2.1f,-2.0f},{-2.1f,-1.5f}, {-2.1f,-1.0f}, {-2.1f,-0.5f}, {-2.1f,0},{-2.1f, 0.5f}, {-2.1f,1.0f},{-2.1f,1.5f}, {-2.1f,2.0f}, {-1.7f,2.3f},{-1.2f,2.3f},{-0.7f,2.3f},{-0.2f,2.3f
}, {0.3f,2.3f}, {0.8f,2.3f}, {1.3f,2.3f},{1.8f,2.3f},{2.3f,1.8f},{2.3f,0.7f} };

// -----------------------------------------------------------------------------
// Transform matrices
// -----------------------------------------------------------------------------
D3DXMATRIX g_mWorld;
D3DXMATRIX g_mView;
D3DXMATRIX g_mProj;

#define M_RADIUS 0.21   // ball radius
#define PI 3.14159265
#define M_HEIGHT 0.01
#define DECREASE_RATE 0.9982

// -----------------------------------------------------------------------------
// CSphere class definition
// -----------------------------------------------------------------------------

class CSphere {
private :
	float					center_x, center_y, center_z;
    float                   m_radius;
	float					m_velocity_x;
	float					m_velocity_z;
	int isblue;

public:
    CSphere(void)
    {
        D3DXMatrixIdentity(&m_mLocal);
        ZeroMemory(&m_mtrl, sizeof(m_mtrl));
        m_radius = 0;
		m_velocity_x = 0;
		m_velocity_z = 0;
        m_pSphereMesh = NULL;
    }
    ~CSphere(void) {}

public:
    bool create(IDirect3DDevice9* pDevice, D3DXCOLOR color = d3d::WHITE)
    {
        if (NULL == pDevice)
            return false;
		
        m_mtrl.Ambient  = color;
        m_mtrl.Diffuse  = color;
        m_mtrl.Specular = color;
        m_mtrl.Emissive = d3d::BLACK;
        m_mtrl.Power    = 5.0f;
		
        if (FAILED(D3DXCreateSphere(pDevice, getRadius(), 50, 50, &m_pSphereMesh, NULL)))
            return false;
        return true;
    }
	
    void destroy(void)
    {
        if (m_pSphereMesh != NULL) {
            m_pSphereMesh->Release();
            m_pSphereMesh = NULL;
        }
    }

    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
    {
        if (NULL == pDevice)
            return;
        pDevice->SetTransform(D3DTS_WORLD, &mWorld);
        pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
        pDevice->SetMaterial(&m_mtrl);
		m_pSphereMesh->DrawSubset(0);
    }
	
    bool hasIntersected(CSphere& ball) 
	{
		D3DXVECTOR3 thispos = this->getCenter();
		D3DXVECTOR3 hitterpos = ball.getCenter();
		
		if (abs(thispos.x - hitterpos.x) <= 2*M_RADIUS && abs(thispos.z - hitterpos.z) <= 2*M_RADIUS) {
			return true;
		}
		return false;
	}
	void setisblue(int a) {
		this->isblue = a;
	}
	
	void hitBy(CSphere& ball) 
	{
		if (hasIntersected(ball)) {
			D3DXVECTOR3 targetpos = this->getCenter();
			D3DXVECTOR3	whitepos = ball.getCenter();
			D3DXVECTOR3 directionv = targetpos - whitepos;
			double theta = (PI/2) - acos(sqrt(pow(targetpos.x - whitepos.x, 2)) / sqrt(pow(targetpos.x - whitepos.x, 2) +
				pow(targetpos.z - whitepos.z, 2)));
			//속도벡터 방향벡터의 단위벡터의 합이 방향
			if (this->isblue == 0) {
				double theta = acos(sqrt(pow(targetpos.x - whitepos.x, 2)) / sqrt(pow(targetpos.x - whitepos.x, 2) +
					pow(targetpos.z - whitepos.z, 2)));	// 기본 1 사분면
				if (targetpos.z - whitepos.z <= 0 && targetpos.x - whitepos.x >= 0) { theta = -theta;
				}	//4 사분면
				if (targetpos.z - whitepos.z >= 0 && targetpos.x - whitepos.x <= 0) { theta = PI - theta; 
				} //2 사분면
				if (targetpos.z - whitepos.z <= 0 && targetpos.x - whitepos.x <= 0) { theta = PI + theta; } // 3 사분면

				double distance = sqrt(pow(targetpos.x - whitepos.x, 2) + pow(targetpos.z - whitepos.z, 2));
				ball.setPower(-3 * cos(theta), -3 * sin(theta));
				this->setCenter(100, 0, 0);
			}
			//파란공에 튀기기
			else {
				double theta = acos(sqrt(pow(targetpos.x - whitepos.x, 2)) / sqrt(pow(targetpos.x - whitepos.x, 2) +
					pow(targetpos.z - whitepos.z, 2)));
				if (targetpos.z - whitepos.z >= 0 && targetpos.x - whitepos.x <= 0) { 
					theta = PI - theta;
					ball.setPower(-3 * cos(theta), -3 * sin(theta));
				} //2 사분면
				else if (targetpos.z - whitepos.z >= 0 && targetpos.x - whitepos.x >= 0) {
					ball.setPower(-3 * cos(theta), -3 * sin(theta));
				}
				else {
					if (whitepos.z >= 5.06f) {
						shootflag = false;
					}
				}
			}
		}
	}

	void ballUpdate(float timeDiff) 
	{
		const float TIME_SCALE = 3.3;
		D3DXVECTOR3 cord = this->getCenter();
		double vx = abs(this->getVelocity_X());
		double vz = abs(this->getVelocity_Z());

		if(vx > 0.01 || vz > 0.01)
		{
			float tX = cord.x + TIME_SCALE*timeDiff*(m_velocity_x);
			float tZ = cord.z + TIME_SCALE*timeDiff*(m_velocity_z);
			this->setCenter(tX, cord.y, tZ);
			
		}
		else { this->setPower(0,0);}
	}

	double getVelocity_X() { return this->m_velocity_x;	}
	double getVelocity_Z() { return this->m_velocity_z; }

	void setPower(double vx, double vz)
	{
		this->m_velocity_x = vx;
		this->m_velocity_z = vz;
	}

	void setCenter(float x, float y, float z)
	{
		D3DXMATRIX m;
		center_x=x;	center_y=y;	center_z=z;
		D3DXMatrixTranslation(&m, x, y, z);
		setLocalTransform(m);
	}
	
	float getRadius(void)  const { return (float)(M_RADIUS);  }
    const D3DXMATRIX& getLocalTransform(void) const { return m_mLocal; }
    void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
    D3DXVECTOR3 getCenter(void) const
    {
        D3DXVECTOR3 org(center_x, center_y, center_z);
        return org;
    }
	
private:
    D3DXMATRIX              m_mLocal;
    D3DMATERIAL9            m_mtrl;
    ID3DXMesh*              m_pSphereMesh;
	
};
CSphere	g_target_blueball;


// -----------------------------------------------------------------------------
// CWall class definition
// -----------------------------------------------------------------------------

class CWall {

private:
	
    float					m_x;
	float					m_z;
	float                   m_width;
    float                   m_depth;
	float					m_height;
	int wallnum;
	
public:
    CWall(void)
    {
        D3DXMatrixIdentity(&m_mLocal);
        ZeroMemory(&m_mtrl, sizeof(m_mtrl));
        m_width = 0;
        m_depth = 0;
        m_pBoundMesh = NULL;
    }
    ~CWall(void) {}
public:
    bool create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::WHITE)
    {
        if (NULL == pDevice)
            return false;
		
        m_mtrl.Ambient  = color;
        m_mtrl.Diffuse  = color;
        m_mtrl.Specular = color;
        m_mtrl.Emissive = d3d::BLACK;
        m_mtrl.Power    = 5.0f;
		
        m_width = iwidth;
        m_depth = idepth;
		
        if (FAILED(D3DXCreateBox(pDevice, iwidth, iheight, idepth, &m_pBoundMesh, NULL)))
            return false;
        return true;
    }
    void destroy(void)
    {
        if (m_pBoundMesh != NULL) {
            m_pBoundMesh->Release();
            m_pBoundMesh = NULL;
        }
    }
    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
    {
        if (NULL == pDevice)
            return;
        pDevice->SetTransform(D3DTS_WORLD, &mWorld);
        pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
        pDevice->SetMaterial(&m_mtrl);
		m_pBoundMesh->DrawSubset(0);
    }
	
	bool hasIntersected(CSphere& ball) 
	{
		D3DXVECTOR3 ballCenter = ball.getCenter();
		float ballRadius = ball.getRadius();
		float width = this->m_width / 2;
		float depth = this->m_depth / 2;
		if (ballCenter.x - ballRadius > this->m_x + width || ballCenter.x + ballRadius < this->m_x - width)
			return false;
		if (ballCenter.z - ballRadius > this->m_z + depth || ballCenter.z + ballRadius < this->m_z - depth)
			return false;
		return true;


	}

	void hitBy(CSphere& ball) 
	{
		float distance = 0;
		float default_length = 0.06f + M_RADIUS;
		D3DXVECTOR3 coord3d = ball.getCenter();
		if (hasIntersected(ball)) {
			if (ball.getVelocity_X() != 0 || ball.getVelocity_Z() != 0) {
				if (this->wallnum == 1) {
					distance = ((default_length - (coord3d.x - this->m_x)) / 2);
					ball.setCenter(coord3d.x - distance * 0.06, M_RADIUS, coord3d.z);
					ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
				}
				if (this->wallnum == 3) {
					distance = ((default_length - (this->m_x - coord3d.x) / 2));
					ball.setCenter(coord3d.x + distance * 0.06, M_RADIUS, coord3d.z);
					ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
				}
				if (this->wallnum == 2) {
					distance = ((default_length - (this->m_z - coord3d.z)) / 2);
					ball.setCenter(coord3d.x, M_RADIUS, coord3d.z + distance*0.06);
					ball.setPower(ball.getVelocity_X(), -ball.getVelocity_Z());
				}
				if (this->wallnum == 4) {
					ball.setPower(0, 0);
					D3DXVECTOR3 tmp = g_target_blueball.getCenter();
					ball.setCenter(tmp.x, M_RADIUS, tmp.z-M_RADIUS*2);
					shootflag = false;
				}
			}
			else {
				ball.setPower(0, 0);
			}
		}
	}    
	
	void setPosition(float x, float y, float z)
	{
		D3DXMATRIX m;
		this->m_x = x;
		this->m_z = z;

		D3DXMatrixTranslation(&m, x, y, z);
		setLocalTransform(m);
	}
	
    float getHeight(void) const { return M_HEIGHT; }
	
	void setwallnum(int x) {
		this->wallnum = x;
	}
	
private :
    void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
	
	D3DXMATRIX              m_mLocal;
    D3DMATERIAL9            m_mtrl;
    ID3DXMesh*              m_pBoundMesh;
};

// -----------------------------------------------------------------------------
// CLight class definition
// -----------------------------------------------------------------------------

class CLight {
public:
    CLight(void)
    {
        static DWORD i = 0;
        m_index = i++;
        D3DXMatrixIdentity(&m_mLocal);
        ::ZeroMemory(&m_lit, sizeof(m_lit));
        m_pMesh = NULL;
        m_bound._center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_bound._radius = 0.0f;
    }
    ~CLight(void) {}
public:
    bool create(IDirect3DDevice9* pDevice, const D3DLIGHT9& lit, float radius = 0.1f)
    {
        if (NULL == pDevice)
            return false;
        if (FAILED(D3DXCreateSphere(pDevice, radius, 10, 10, &m_pMesh, NULL)))
            return false;
		
        m_bound._center = lit.Position;
        m_bound._radius = radius;
		
        m_lit.Type          = lit.Type;
        m_lit.Diffuse       = lit.Diffuse;
        m_lit.Specular      = lit.Specular;
        m_lit.Ambient       = lit.Ambient;
        m_lit.Position      = lit.Position;
        m_lit.Direction     = lit.Direction;
        m_lit.Range         = lit.Range;
        m_lit.Falloff       = lit.Falloff;
        m_lit.Attenuation0  = lit.Attenuation0;
        m_lit.Attenuation1  = lit.Attenuation1;
        m_lit.Attenuation2  = lit.Attenuation2;
        m_lit.Theta         = lit.Theta;
        m_lit.Phi           = lit.Phi;
        return true;
    }
    void destroy(void)
    {
        if (m_pMesh != NULL) {
            m_pMesh->Release();
            m_pMesh = NULL;
        }
    }
    bool setLight(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
    {
        if (NULL == pDevice)
            return false;
		
        D3DXVECTOR3 pos(m_bound._center);
        D3DXVec3TransformCoord(&pos, &pos, &m_mLocal);
        D3DXVec3TransformCoord(&pos, &pos, &mWorld);
        m_lit.Position = pos;
		
        pDevice->SetLight(m_index, &m_lit);
        pDevice->LightEnable(m_index, TRUE);
        return true;
    }

    void draw(IDirect3DDevice9* pDevice)
    {
        if (NULL == pDevice)
            return;
        D3DXMATRIX m;
        D3DXMatrixTranslation(&m, m_lit.Position.x, m_lit.Position.y, m_lit.Position.z);
        pDevice->SetTransform(D3DTS_WORLD, &m);
        pDevice->SetMaterial(&d3d::WHITE_MTRL);
        m_pMesh->DrawSubset(0);
    }

    D3DXVECTOR3 getPosition(void) const { return D3DXVECTOR3(m_lit.Position); }

private:
    DWORD               m_index;
    D3DXMATRIX          m_mLocal;
    D3DLIGHT9           m_lit;
    ID3DXMesh*          m_pMesh;
    d3d::BoundingSphere m_bound;
};


// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
CWall	g_legoPlane;
CWall	g_legowall[4];
CSphere	g_sphere[46];
CSphere g_shootball;
CLight	g_light;


double g_camera_pos[3] = {0.0, 5.0, -8.0};

// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------


void destroyAllLegoBlock(void)
{
}

// initialization
bool Setup()
{
	int i;
	shootflag = false;

    D3DXMatrixIdentity(&g_mWorld);
    D3DXMatrixIdentity(&g_mView);
    D3DXMatrixIdentity(&g_mProj);

	// create plane and set the position
    if (false == g_legoPlane.create(Device, -1, -1, 6, 0.03f, 9, d3d::GREEN)) return false;
    g_legoPlane.setPosition(0.0f, -0.0006f / 5, 0.0f);
	
	// create walls and set the position. note that there are four walls
	if (false == g_legowall[0].create(Device, -1, -1, 6.24f, 0.0f, 0.12f, d3d::WHITE)) return false;
	g_legowall[0].setPosition(0.0f, 10.00f, 5.2f);
	g_legowall[0].setwallnum(4);
	if (false == g_legowall[1].create(Device, -1, -1, 6.24f, 0.3f, 0.12f, d3d::BLACK)) return false;
	g_legowall[1].setPosition(0.0f, 0.12f, -4.56f);
	g_legowall[1].setwallnum(2);
	if (false == g_legowall[2].create(Device, -1, -1, 0.12f, 0.3f, 9, d3d::BLACK)) return false;
	g_legowall[2].setPosition(3.06f, 0.12f, 0.0f);
	g_legowall[2].setwallnum(1);
	if (false == g_legowall[3].create(Device, -1, -1, 0.12f, 0.3f, 9, d3d::BLACK)) return false;
	g_legowall[3].setPosition(-3.06f, 0.12f, 0.0f);
	g_legowall[3].setwallnum(3);

	// create four balls and set the position
	for (i=0;i<46;i++) {
		if (false == g_sphere[i].create(Device,d3d:: YELLOW)) return false;
		g_sphere[i].setCenter(spherePos[i][0], (float)M_RADIUS , spherePos[i][1]);
		g_sphere[i].setPower(0,0);
		g_sphere[i].setisblue(0);
	}
	
	// create blue ball for set direction
    if (false == g_target_blueball.create(Device, d3d::GREEN)) return false;
	g_target_blueball.setCenter(.0f, (float)M_RADIUS , 4.56f);
	g_target_blueball.setisblue(1);
	if (false == g_shootball.create(Device, d3d::RED)) return false;
	g_shootball.setCenter(.0f, (float)M_RADIUS, 4.56f-float(M_RADIUS)*2);
	
	// light setting 
    D3DLIGHT9 lit;
    ::ZeroMemory(&lit, sizeof(lit));
    lit.Type         = D3DLIGHT_POINT;
    lit.Diffuse      = d3d::WHITE; 
	lit.Specular     = d3d::WHITE * 0.9f;
    lit.Ambient      = d3d::WHITE * 0.9f;
    lit.Position     = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
    lit.Range        = 100.0f;
    lit.Attenuation0 = 0.0f;
    lit.Attenuation1 = 0.9f;
    lit.Attenuation2 = 0.0f;
    if (false == g_light.create(Device, lit))
        return false;
	
	// Position and aim the camera.
	D3DXVECTOR3 pos(0.0f, 10.0f, 10.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_mView, &pos, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &g_mView);
	
	// Set the projection matrix.
	D3DXMatrixPerspectiveFovLH(&g_mProj, D3DX_PI / 4,
        (float)Width / (float)Height, 1.0f, 100.0f);
	Device->SetTransform(D3DTS_PROJECTION, &g_mProj);
	
    // Set render states.
    Device->SetRenderState(D3DRS_LIGHTING, TRUE);
    Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
    Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	
	g_light.setLight(Device, g_mWorld);
	return true;
}

void Cleanup(void)
{
    g_legoPlane.destroy();
	for(int i = 0 ; i < 4; i++) {
		g_legowall[i].destroy();
	}
    destroyAllLegoBlock();
    g_light.destroy();
}


// timeDelta represents the time between the current image frame and the last image frame.
// the distance of moving balls should be "velocity * timeDelta"
bool Display(float timeDelta)
{
	int i=0;
	int j = 0;


	if( Device )
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00afafaf, 1.0f, 0);
		Device->BeginScene();
		
		// update the position of each ball. during update, check whether each ball hit by walls.
		for(i = 0; i < 46; i++) {
			g_sphere[i].ballUpdate(timeDelta);
			for(j = 0; j < 4; j++){ g_legowall[j].hitBy(g_shootball); }
		}
		g_shootball.ballUpdate(timeDelta);
		// check whether any two balls hit together and update the direction of balls
		for(i = 0 ;i < 46; i++){
				g_sphere[i].hitBy(g_shootball);
		}
		g_target_blueball.hitBy(g_shootball);
		// draw plane, walls, and spheres
		g_legoPlane.draw(Device, g_mWorld);
		for (i = 0; i < 4; i++) {
			g_legowall[i].draw(Device, g_mWorld);
		}
		for (i=0;i<46;i++) 	{
			g_sphere[i].draw(Device, g_mWorld);
		}
		g_target_blueball.draw(Device, g_mWorld);
		g_shootball.draw(Device, g_mWorld);
        g_light.draw(Device);
		
		Device->EndScene();
		Device->Present(0, 0, 0, 0);
		Device->SetTexture( 0, NULL );
	}
	return true;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool wire = false;
	static bool isReset = true;
    static int old_x = 0;
    static int old_y = 0;
    static enum { WORLD_MOVE, LIGHT_MOVE, BLOCK_MOVE } move = WORLD_MOVE;
	
	switch( msg ) {
	case WM_DESTROY:
        {
			::PostQuitMessage(0);
			break;
        }
	//키보드 컨트롤
	case WM_KEYDOWN:
        {
            switch (wParam) {
            case VK_ESCAPE:
				::DestroyWindow(hwnd);
                break;
            case VK_RETURN:
                if (NULL != Device) {
                    wire = !wire;
                    Device->SetRenderState(D3DRS_FILLMODE,
                        (wire ? D3DFILL_WIREFRAME : D3DFILL_SOLID));
                }
                break;
            case VK_SPACE:
				if (shootflag == false) {
					D3DXVECTOR3 targetpos = g_target_blueball.getCenter();
					D3DXVECTOR3	whitepos = g_shootball.getCenter();
					shootflag = true;
					g_shootball.setPower(0, -2.5);
				}

				break;

			}
			break;
        }
	
	case WM_MOUSEMOVE:
        {
            int new_x = LOWORD(lParam);
            int new_y = HIWORD(lParam);
			float dx;
			float dy;
			
            if (LOWORD(wParam) & MK_LBUTTON) {
				
                if (isReset) {
                    isReset = false;
                } else {
                    D3DXVECTOR3 vDist;
                    D3DXVECTOR3 vTrans;
                    D3DXMATRIX mTrans;
                    D3DXMATRIX mX;
                    D3DXMATRIX mY;
					/*
                    switch (move) {
                    case WORLD_MOVE:
                        dx = (old_x - new_x) * 0.01f;
                        dy = (old_y - new_y) * 0.01f;
                        D3DXMatrixRotationY(&mX, dx);
                        D3DXMatrixRotationX(&mY, dy);
                        g_mWorld = g_mWorld * mX * mY;
                        break;
                    }*/
                }
				
                old_x = new_x;
                old_y = new_y;

            } else {
                isReset = true;
				
				if (LOWORD(wParam) & MK_RBUTTON) {
					dx = (old_x - new_x);// * 0.01f;
					dy = (old_y - new_y);// * 0.01f;
		
					D3DXVECTOR3 coord3d=g_target_blueball.getCenter();
					if (shootflag == false) {
						if (coord3d.x + dx * (0.007f) > 3.06f) {
							g_target_blueball.setCenter(3.06f, coord3d.y, 4.56f);//coord3d.z+dy*(-0.007f) );
							g_shootball.setCenter(3.06f, coord3d.y, 4.56f - float(M_RADIUS) * 2);
						}
						else if (coord3d.x + dx * (0.007f) < -3.06f) {
							g_target_blueball.setCenter(-3.06f, coord3d.y, 4.56f);//coord3d.z+dy*(-0.007f) );
							g_shootball.setCenter(-3.06f, coord3d.y, 4.56f - float(M_RADIUS) * 2);
						}
						else {
							g_target_blueball.setCenter(coord3d.x + dx * (0.007f), coord3d.y, 4.56f);
							g_shootball.setCenter(coord3d.x + dx * (0.007f), coord3d.y, 4.56f - float(M_RADIUS) * 2);
						}
					}
					else {
						if (coord3d.x + dx * (0.007f) > 3.06f) {
							g_target_blueball.setCenter(3.06f, coord3d.y, 4.56f);//coord3d.z+dy*(-0.007f) );
						}
						else if (coord3d.x + dx * (0.007f) < -3.06f) {
							g_target_blueball.setCenter(-3.06f, coord3d.y, 4.56f);//coord3d.z+dy*(-0.007f) );
						}
						else {
							g_target_blueball.setCenter(coord3d.x + dx * (0.007f), coord3d.y, 4.56f);
						}
					}
				}
				old_x = new_x;
				old_y = new_y;
				
                move = WORLD_MOVE;
            }
            break;
        }
	}
	
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
    srand(static_cast<unsigned int>(time(NULL)));
	
	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
	
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}
	
	d3d::EnterMsgLoop( Display );
	
	Cleanup();
	
	Device->Release();
	
	return 0;
}