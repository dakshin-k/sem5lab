/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shopping.metadata;
/**
 *
 * @author Dakshin
 */
public class Login {
    private String username;
    private int custType;
    private int custId;

    public Login(String username, int id,int custType) {
        this.username = username;
        this.custType = custType;
        custId=id;
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
    
}
