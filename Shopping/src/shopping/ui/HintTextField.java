/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shopping.ui;

import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import javax.swing.JTextField;

/**
 *
 * @author Dakshin
 */
public class HintTextField extends JTextField implements FocusListener{
    

  private String hint;
  private boolean showingHint;

  public HintTextField(final String hint) {
    super(hint);
    this.hint = hint;
    this.showingHint = true;
    super.addFocusListener(this);
  }
  public HintTextField() {
    super();
    hint="";
    this.showingHint = false;
    super.addFocusListener(this);
  }

  public void setHint(String hint){
      this.hint=hint;
      if(this.getText().isEmpty())
      {
          showingHint=true;
          super.setText(hint);
      }
  }
  @Override
  public void focusGained(FocusEvent e) {
    if(this.getText().isEmpty()) {
      super.setText("");
      showingHint = false;
    }
  }
  @Override
  public void focusLost(FocusEvent e) {
    if(this.getText().isEmpty()) {
      super.setText(hint);
      showingHint = true;
    }
  }

  @Override
  public String getText() {
    return showingHint ? "" : super.getText();
  }
}