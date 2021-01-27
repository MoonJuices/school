/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testproject01;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.text.Text;
import javafx.scene.shape.Circle;
import javafx.scene.paint.Color;
import javafx.scene.paint.CycleMethod;
import javafx.scene.paint.RadialGradient;
import javafx.scene.paint.Stop;

/**
 *
 * @author Lucas
 */
public class FXMLDocumentController implements Initializable {
    
    @FXML
    //private Label label;
    private Text text1, text2, text3;
    public Circle circle;
    
    @FXML
    private void handleButtonActionGradient(ActionEvent event) 
    {
        System.out.println("Gradient Generated");
        
        int r1 = (int)(Math.random()*256);
        int g1 = (int)(Math.random()*256);
        int b1 = (int)(Math.random()*256);
        int r2 = (int)(Math.random()*256);
        int g2 = (int)(Math.random()*256);
        int b2 = (int)(Math.random()*256);
        int r3 = (int)(Math.random()*256);
        int g3 = (int)(Math.random()*256);
        int b3 = (int)(Math.random()*256);
        
        text1.setText("Color 1: " + r1 + " " + g1 + " " + b1);
        text2.setText("Color 2: " + r2 + " " + g2 + " " + b2);
        text3.setText("Color 3: " + r3 + " " + g3 + " " + b3);
        
        Stop[] gradientStops = new Stop[]
        {
          new Stop(0, Color.rgb(r1, g1, b1)),
          new Stop(0.8, Color.rgb(r2, g2, b2)),
          new Stop(1, Color.rgb(r3, g3, b3))
        };
        
        RadialGradient rg = new RadialGradient(0.1, 0.1, 5, 5, 7, true, CycleMethod.NO_CYCLE, gradientStops);
        
        circle.setFill(rg);
    }
    
    @FXML
    private void handleButtonActionColor(ActionEvent event)
    {
        System.out.println("Color Generated");
        
        int r1 = (int)(Math.random()*256);
        int g1 = (int)(Math.random()*256);
        int b1 = (int)(Math.random()*256);
        
        text1.setText("");
        text2.setText("Color: " + r1 + " " + g1 + " " + b1);
        text3.setText("");
        
        circle.setFill(Color.rgb(r1,g1,b1));
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    
    
}
