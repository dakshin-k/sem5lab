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
public class CartItem {
    private Product prod;
    private int qty;

    public CartItem(Product prof, int qty) {
        this.prod = prof;
        this.qty = qty;
    }
    public CartItem(ResultSet rs) 
    {
        try {
            ResultSet rs2=DataBase.select("select * from products where pid = "+rs.getInt(2));
            rs2.next();
            this.prod=new Product(rs2);
            this.qty=rs.getInt(3);
        } catch (SQLException ex) {
            Logger.getLogger(CartItem.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public Product getProd() {
        return prod;
    }

    public int getQty() {
        return qty;
    }

    public void setQty(int qty) {
        this.qty = qty;
    }
    public boolean equals(Product i)
    {
        return prod.equals(i);
    }
}
