/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shopping;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Dakshin
 */
public class DataBase {
    static Connection conn;
    public static void connect()
    {
        if(conn!=null) return;
        try {  
            conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/db","root","abcd");
            System.out.println("Connected to Database");
        } catch (SQLException ex) {
            Logger.getLogger(DataBase.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
