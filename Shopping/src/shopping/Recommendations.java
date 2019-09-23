/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shopping;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import shopping.metadata.Login;
import shopping.metadata.Product;

/**
 *
 * @author Dakshin
 */
public class Recommendations {
    static Product[] getRecommendations(Login login)
    {
        Product[] prod=new Product[3];
        try {
            String cid=String.valueOf(login.getId());
            //todo: for now its just returning 3 random items
            // needs to be based on order history
            
            
            ResultSet rs=DataBase.select("select * from products,inventory"
                    + " where products.pid=inventory.pid and qty>0"
                    + " order by rand() limit 3");
            if(!rs.next()) return null;
            for(int i=0;i<3;i++)
            {
                prod[i]=new Product(rs);
                rs.next();
            }
        } catch (SQLException ex) {
            Logger.getLogger(Recommendations.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    
    return prod;
    }
}
