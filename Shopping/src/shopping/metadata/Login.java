/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shopping.metadata;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import shopping.DataBase;

/**
 *
 * @author Dakshin
 */
public class Login {
    private String username;
    private int custType;
    private int custId;
    private String name=null;
    public Login(String username, int id,int custType) {
        this.username = username;
        this.custType = custType;
        custId=id;
        if(custType==2) //customer
        {
            ResultSet rs=DataBase.select("select name from customers where cid = ?",String.valueOf(custId));
            try {
                rs.next();
                this.name=rs.getNString(1);
            } catch (SQLException ex) {
                Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public String getUsername() {
        return username;
    }
    public int getId(){
        return custId;
    }
    public int getCustType() {
        return custType;
    }

    public String getName() {
        return this.name;
    }
    
}
