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

    public ArrayList<CartItem> getItems() {
        return cart;
    }
    public int getSize()
    {
        return cart.size();
    }

    public void remove(Product p2) {
        int i;
        for(i=0;i<cart.size();i++)
        {
            if(cart.get(i).equals(p2)) break;
        }
        if(i==cart.size())
            // idk what just happened; f it
            return;
        cart.remove(i);
        update();
    }
    public float getTotal()
    {
        float ans=0;
        for(CartItem i:cart)
        {
            ans+=i.getProd().getPrice()*i.getQty();
        }
        return ans;
    }
    public String placeOrder()
    {
        String ono="";
        try {
            //insert into orders
            String insert="insert into orders values(null,"+cid+",curdate())";
            DataBase.insert(insert);
            ResultSet rs=DataBase.select("select last_insert_id()");
            rs.next();
            ono=String.valueOf(rs.getInt(1));
            for(CartItem i:cart) 
            {
                DataBase.insert("insert into order_deets values(?,?,?)", 
                        ono,String.valueOf(i.getProd().getPid()),
                        String.valueOf(i.getQty()));
                //assign this order to staff with the least number of deliveries
                String sql=
                        "select sid from pending_order_no "
                        + "order by n asc";
                rs=DataBase.select(sql);
                rs.next();
                String sid=String.valueOf(rs.getInt(1));
                DataBase.insert("insert into pending_orders values(?,?)", sid,ono);
                //coz delete and update have same internal mechanism, using delete instead of update
                DataBase.delete("update pending_order_no set n = n+1 where sid="+sid);
            }
            
        } catch (SQLException ex) {
            Logger.getLogger(Cart.class.getName()).log(Level.SEVERE, null, ex);
            return "";
        }
        clear();
        return ono;
    }
    public void clear(){
        cart.clear();
        update();
    }
}
