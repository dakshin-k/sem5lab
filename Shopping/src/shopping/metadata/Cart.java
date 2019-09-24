/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shopping.metadata;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import shopping.DataBase;

/**
 *
 * @author Dakshin
 */
public class Cart {
    private ArrayList<CartItem> cart=new ArrayList<>();
    private int cid;
    
    public Cart(Login login) 
    {
        this.cid=login.getId();
        // get cart contents from the database
        ResultSet rs=DataBase.select(
        "select * from cart where cid = "+login.getId());
        try {
            while(rs.next())
            {
                cart.add(new CartItem(rs));
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cart.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public void add(Product p)
    {
        int q=1;
        for(int i=0;i<cart.size();i++)
        {
            if(p.equals(cart.get(i).getProd()))
            {
                q+=cart.get(i).getQty();
                cart.remove(i);
            }
        }
        cart.add(new CartItem(p,q));
    }
    public void update()
    {
        DataBase.delete("delete from cart where cid = "+cid);
        cart.forEach((item) -> {
            DataBase.insert("insert into cart values(?,?,?)", String.valueOf(cid),
                    String.valueOf(item.getProd().getPid()),
                    String.valueOf(item.getQty()));
        });
    }
    public int getSize()
    {
        return cart.size();
    }
}
