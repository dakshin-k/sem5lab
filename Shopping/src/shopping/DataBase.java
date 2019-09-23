/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shopping;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import shopping.metadata.Login;

/**
 *
 * @author Dakshin
 */
public class DataBase {
    static Connection conn;
     public static String insert(String sql,String... arg)
    {
        return execute(prepareStatement(sql,arg));
    }
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
    public static ResultSet select(String sql) 
    {
        try {
            return conn.prepareStatement(sql).executeQuery();
        } catch (SQLException ex) {
            Logger.getLogger(DataBase.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(null, "select failed");
            return null;
        }
    }
    public static ResultSet select(String sql,String... arg){
        try{
            PreparedStatement ps=conn.prepareStatement(sql);
            System.out.println(arg[0]);
            for(int i=1;i<=arg.length;i++)
                ps.setString(i, arg[i-1]);
            return ps.executeQuery();
        }catch(SQLException e){
            JOptionPane.showMessageDialog(null, "Select failed");
            Logger.getLogger(DataBase.class.getName()).log(Level.SEVERE, null, e);
            return null;
        }
    }
    public static ResultSet select(PreparedStatement ps)
    {
        try {
            return ps.executeQuery();
        } catch (SQLException ex) {
            Logger.getLogger(DataBase.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
    public static Login login(String user,String pwd)
    {
        try {
            shopping.DataBase.connect();
            String sql="select password,usertype,cid from users where username = \""+user+"\"";
            ResultSet rs=DataBase.select(sql);
            if(!rs.next())
                return null;
            String actual=rs.getNString(1);
            int custType=rs.getInt(2);
            int id=rs.getInt(3);
            if(actual.equals(pwd))
                return new Login(user,id,custType);
            return null;
        } catch (SQLException ex) {
            Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
    public static PreparedStatement prepareStatement(String sql)
    {
        try {
            return conn.prepareStatement(sql);
        } catch (SQLException ex) {
            Logger.getLogger(DataBase.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(null, "prepareStatement error");
            return null;
        }
    }
    public static PreparedStatement prepareStatement(String sql,String ...arg)
    {
        try {
            PreparedStatement ps= conn.prepareStatement(sql);
            for(int i=1;i<=arg.length;i++)
                ps.setString(i, arg[i-1]);
            return ps;
        } catch (SQLException ex) {
            Logger.getLogger(DataBase.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(null, "prepareStatement error");
            return null;
        }
    }
    public static String execute(PreparedStatement ps)
    {
        try
        {
            ps.execute();
            return "success";
        } catch(SQLException e)
        {
            //JOptionPane.showMessageDialog(null, "Failed to update records");
            Logger.getLogger(DataBase.class.getName()).log(Level.SEVERE, null, e);
            return e.toString();
        }
    }
   
}
