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

/**
 *
 * @author Dakshin
 */
public class Product {
    private int pid;
    private String name,imgpath,sdesc,ldesc;
    float price;

    public Product(ResultSet rs) {
        try {
            //assumes that rs is from table products and rs.next() has been called already
            pid=rs.getInt(1);
            name=rs.getNString(2);
            imgpath=rs.getNString(3);
            sdesc=rs.getNString(4);
            ldesc=rs.getNString(5);
            price=rs.getFloat(6);
            //System.out.println("New product object: "+name+","+pid);
        } catch (SQLException ex) {
            Logger.getLogger(Product.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public Product(int pid, String name, String imgpath, String sdesc, String ldesc, float price) {
        this.pid = pid;
        this.name = name;
        this.imgpath = imgpath;
        this.sdesc = sdesc;
        this.ldesc = ldesc;
        this.price = price;
    }

    public int getPid() {
        return pid;
    }

    public String getName() {
        return name;
    }

    public String getImgpath() {
        return imgpath;
    }

    public String getSdesc() {
        return sdesc;
    }

    public String getLdesc() {
        return ldesc;
    }

    public float getPrice() {
        return price;
    }
    public String toString()
    {
        return pid+" "+name;
    }
}
