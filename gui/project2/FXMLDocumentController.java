/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testproject02;

import java.net.URL;
import java.util.HashMap;
import java.util.Map;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.PieChart;
import javafx.scene.control.Label;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.scene.layout.HBox;
import javafx.scene.text.Text;
import javafx.scene.Scene;
import javafx.event.EventHandler;
import javafx.event.ActionEvent;

/**
 *
 * @author Lucas
 */
public class FXMLDocumentController implements Initializable {
    
    private Map<String, Label> cloudLabels;
    private Map<String, PieChart.Data> cloudWedges;
    
    @FXML
    private Button addB;
    
    @FXML
    private Button clearB;
    
    @FXML
    private Button quitB;
    
    @FXML
    private PieChart pieChart;
    
    @FXML
    private TextField textField;
    
    @FXML
    private AnchorPane anchorPane;
    
    public boolean causesIntersection(Label newWord)
    {
        for(Node word: anchorPane.getChildren())
        {
            Label oldWord = (Label) word;
            if(newWord!=oldWord)
            {
                if(newWord.getBoundsInParent().intersects(oldWord.getBoundsInParent()))
                {
                    return true;
                }
            }
        }
        return false;
    }
    
    public void placeWord(Label newWord)
    {
        boolean intersects = false;
        double radius = 0;
        double angle = 0;
        double middleX = anchorPane.getWidth()/2;
        double middleY = anchorPane.getHeight()/2;
        do
        {
            double xPos = middleX + radius*Math.cos(angle);
            double yPos = middleY + radius*Math.sin(angle);
            newWord.setLayoutX(xPos);
            newWord.setLayoutY(yPos);
            newWord.setRotate(0);
            intersects = causesIntersection(newWord);
            if(intersects)
            {
                newWord.setRotate(90);
                intersects = causesIntersection(newWord);
            }
            radius+=0.5;
            angle+=0.1;
        }while(intersects);
        
        //LABEL MOUSE CLICK - BUG
        PieChart.Data wedge = new PieChart.Data(newWord.getText(), 1);
        newWord.setOnMouseClicked(mev -> growWedge(mev, wedge, newWord.getText()));
    }
    
    private void addWedge(String newWord)
    {
        if (cloudWedges.get(newWord) != null)
        {
            return;
        }
        PieChart.Data wedge = new PieChart.Data(newWord, 1);
        cloudWedges.put(newWord, wedge);
        pieChart.getData().add(wedge);
        wedge.getNode().setOnMouseClicked(mev -> growWedge(mev, wedge, newWord));
    }
    
    @FXML
    private void growWedge(MouseEvent e, PieChart.Data w, String newWord)
    {
        w.setPieValue(w.getPieValue() +1 );
        for(Node word: anchorPane.getChildren())
        {
            Label oldWord = (Label) word;
            if(newWord==oldWord.getText())
            {
                double currentFontSize = oldWord.getFont().getSize();
                oldWord.setFont(new Font(oldWord.getFont().getName(),currentFontSize+2));
                if(causesIntersection(oldWord))
                {
                    placeWord(oldWord);
                }
            }
        }
    }
    
    @FXML
    private void handleButtonActionAdd(ActionEvent event) 
    {
        Label newWord = cloudLabels.get(textField.getText());
        if(newWord!=null)
        {
            double currentFontSize = newWord.getFont().getSize();
            newWord.setFont(new Font(newWord.getFont().getName(),currentFontSize+2));
            placeWord(newWord);
            PieChart.Data wedge = cloudWedges.get(newWord.getText());
            wedge.setPieValue(wedge.getPieValue()+1);
            return;
        }
        newWord = new Label(textField.getText());
        anchorPane.getChildren().add(newWord);
        anchorPane.applyCss();
        anchorPane.layout();
        cloudLabels.put(newWord.getText(),newWord);
        placeWord(newWord);
        addWedge(newWord.getText());
    }
    
    @FXML
    private void handleButtonActionClear(ActionEvent event)
    {
        Stage clearStage = new Stage();
        
        Text txt = new Text();
        Button btn1 = new Button();
        Button btn2 = new Button();
        
        txt.setText("CLEAR ALL?");
        btn1.setText("YES");
        btn2.setText("NO");
        
        HBox root = new HBox();
        root.getChildren().add(txt);
        root.getChildren().add(btn1);
        root.getChildren().add(btn2);
        clearStage.setScene(new Scene(root, 150, 50));
        clearStage.show();
        
        EventHandler<ActionEvent> yesevent = new EventHandler<ActionEvent>() { 
            public void handle(ActionEvent e) 
            { 
                anchorPane.getChildren().clear();
                pieChart.getData().clear();
                clearStage.close();
            } 
        };
        btn1.setOnAction(yesevent);
        EventHandler<ActionEvent> noevent = new EventHandler<ActionEvent>() { 
            public void handle(ActionEvent e) 
            { 
                clearStage.close();
            } 
        };
        btn2.setOnAction(noevent);
    }
    
    @FXML
    private void handleButtonActionQuit(ActionEvent event)
    {
        Stage quitStage = new Stage();
        
        Text txt = new Text();
        Button btn1 = new Button();
        Button btn2 = new Button();
        
        txt.setText("QUIT?");
        btn1.setText("YES");
        btn2.setText("NO");
        
        HBox root = new HBox();
        root.getChildren().add(txt);
        root.getChildren().add(btn1);
        root.getChildren().add(btn2);
        quitStage.setScene(new Scene(root, 150, 50));
        quitStage.show();
        
        EventHandler<ActionEvent> yesevent = new EventHandler<ActionEvent>() { 
            public void handle(ActionEvent e) 
            { 
                System.exit(0);
            } 
        };
        btn1.setOnAction(yesevent);
        EventHandler<ActionEvent> noevent = new EventHandler<ActionEvent>() { 
            public void handle(ActionEvent e) 
            { 
                quitStage.close();
            } 
        };
        btn2.setOnAction(noevent);
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
        cloudWedges = new HashMap<String, PieChart.Data>();
        cloudLabels = new HashMap<String, Label>();
    }     
}
