package com.datamartstaging;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class DatamartDBConnect {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
        try
        {
       	 Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");

            String userName = "borg_db";
            String password = "MSsql@2012";
            String url = "jdbc:sqlserver://fsi2wks16547.tatatechnologies.com:56000"+";databaseName=SyncroSpec Data Mart";
            Connection con = DriverManager.getConnection(url, userName, password);
            Statement s1 = con.createStatement();
           System.out.println("the connection"+ s1);
           
           
          // s1.executeUpdate("INSERT INTO WC2TC_PART " + 
                 //  "VALUES('666','2','0.3','test','DEsc','infodba',NULL,'infodba',NULL,'work',NULL,'as','1','0','0','123',0,0,NULL,0,NULL,0,NULL,'123');");
           
           //s1.executeUpdate("INSERT INTO STAGING_DOCUMENT(DOCUMENTNUMBER,DOCUMENTREVISION,ITERATION,NAME,OBJECT_DESC,CREATED_BY,CREATION_DATE,LAST_MODIFIED_BY,LAST_MODIFIED_DATE,LIFECYCLE_STATE,RELEASE_DATE,DOCUMENT_TYPE,CUSTOMER_SUPL_REV,FILE_PATH,FILE_ORIGINAL_NAME,FILE_TYPE,MIGRATION_TYPE,MIGRATION_DECISION,WC_EXTRACTION_DATE,WC_MIG_STATUS,TC_GROUP,TC_PROCESS_STATUS,TC_PROCESS_DATE)  values ('00001','2','0.3', 'test','desc','infodba',NULL,'infodba',NULL,'work',NULL,'as',NULL,NULL,'wtdocument',NULL,0,0,NULL,NULL,NULL,0,NULL)");
			 
			
       
           con.close(); 
           

        } catch (Exception e)
        {
       	 System.err.println("Got an exception! "); 
            e.printStackTrace();
        }
           
	}

}
