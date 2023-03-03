import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
import java.util.Scanner;
public class project4 {
	static final String DB_URL= "jdbc:mysql://localhost/KREAM?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";
	static final String USER = "root";
	static final String PASS = "12345678";
	static final String QUERY = "select * from account_info";

	public static void searchuserinfo(Scanner scanner){
		Connection conn = null;
		PreparedStatement pstmt = null;
		PreparedStatement pstmt2 = null;
		ResultSet rs = null;
		ResultSet rt = null;
		System.out.println("닉네임 입력 시 닉네임에 관한 계정 정보와 wishlist 목록을 제공해드립니다.");
		System.out.println("닉네임을 입력해주세요!");
		String Name = scanner.next();
		
		try {
			conn = DriverManager.getConnection(DB_URL,USER,PASS);
			String query = "select nickname, email, point, address, introduction, image, membership\n"
					+ "from account_info\n"
					+ "where nickname = (?)";
			String query2 = "select size , product_id\n"
					+ "from wishlist\n"
					+ "where id in (select id from account_info where nickname = (?))";
			pstmt = conn.prepareStatement(query);
			pstmt.setString(1,Name);
			rs = pstmt.executeQuery();
			pstmt2 = conn.prepareStatement(query2);
			pstmt2.setString(1,Name);
			rt = pstmt2.executeQuery();
			while(rs.next()) {
				System.out.println(rs.getString("email") + " "+ rs.getInt("point") + " " + rs.getString("membership"));
			}
			
			while(rt.next()) {
				System.out.println(rt.getString("size") + " " + rt.getString("product_id"));
			}
			conn.close();
			}catch (SQLException ex) {
				System.out.println("SQLException" + ex);
			}
	}
	public static void sortbytrade(Scanner scanner) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		System.out.println("원하시는 카테고리의 인기순 정렬 및 상품 정보를 제공해드립니다.");
		System.out.println("category를 입력해주세요 -> Shoes, clothes .. ");
		String a = scanner.next();
		try {
		conn = DriverManager.getConnection(DB_URL,USER,PASS);
		String query = "select product_name, brand, count(*) as cnt , image\n"
				+ "from product_info as A , bidding as B\n"
				+ "where A.product_id = B.product_id and A.category = (?) \n"
				+ "group by A.product_id\n"
				+ "order by count(*) DESC";
		pstmt = conn.prepareStatement(query);
		pstmt.setString(1,a);
		rs = pstmt.executeQuery();
		int Num = 1;
		while(rs.next()) {
			System.out.println(rs.getString("product_name") + " "+ rs.getString("brand") +" 거래개수 : " +  rs.getString("cnt") + " 제품 이미지 : " + rs.getString("image"));
			Num++;
		}
		conn.close();
		}
		catch (SQLException ex) {
			System.out.println("SQLException" + ex);
		}
	}

	public static void main(String[] args) throws ClassNotFoundException, SQLException{
		while(true) {
			Scanner scanner = new Scanner(System.in);
			System.out.println("-- 안녕하세요 한정판 거래 플랫폼 KREAM입니다 ---");
			System.out.println("-- 원하는 기능을 선택해주세요 ---");
			System.out.println("-- 1. 원하는 닉네임의 계정정보와 wishlist를 제공 ---");
			System.out.println("-- 2. 원하는 카테고리 내에서 가장 많이 거래된 제품의 순서대로 정렬 및 상품에 관한 정보 제공 ---");
			System.out.println("-- 3. 프로그램 종료 ---");
			String input = scanner.next();
			
			if(input.equals("1")) {
				searchuserinfo(scanner);
			}
			if(input.equals("2")) {
				sortbytrade(scanner);
			}
			if(input.equals("3")){
				System.out.println("프로그램을 종료합니다.");
				break;
			}
		}
		
	}

}

