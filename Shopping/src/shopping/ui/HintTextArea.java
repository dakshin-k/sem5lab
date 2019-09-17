/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shopping.ui;

import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import javax.swing.JTextArea;

/**
 *
 * @author Dakshin
 */
public class HintTextArea extends JTextArea implements FocusListener {

  private String hint;
  private boolean showingHint;

  public HintTextArea(final String hint) {
    super(hint);
    this.hint = hint;
    this.showingHint = true;
    super.addFocusListener(this);
  }
  
  public HintTextArea() {
    super();
    this.hint ="";
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