/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cs344_finalproject;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import javafx.scene.shape.Polygon;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import javafx.scene.Cursor;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import java.awt.geom.Point2D;
import java.io.File;
import javafx.application.HostServices;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.transform.Rotate;

/**
 *
 * @author Lucas
 */
public class CS344_FinalProject extends Application {
    
    double orgSceneX, orgSceneY;
    
    private Polygon createHexagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, Color color){
        Polygon hexagon = new Polygon();
        hexagon.getPoints().addAll(new Double[]{
            x1, y1,
            x2, y2,
            x3, y3,
            x4, y4,
            x5, y5,
            x6, y6,
        });
        hexagon.setStroke(Color.BLACK);
        hexagon.setStrokeWidth(7);
        hexagon.setFill(color);
        hexagon.setCursor(Cursor.HAND);
        
        final ObjectProperty<Point2D> mousePosition = new SimpleObjectProperty<>();

    hexagon.setOnMousePressed(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            if(event.isControlDown()){
                mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
                hexagon.toFront();
            }
        }
    });

    hexagon.setOnMouseDragged(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            if(event.isControlDown()){
                double deltaX = event.getSceneX() - mousePosition.get().getX();
                double deltaY = event.getSceneY() - mousePosition.get().getY();
                hexagon.setLayoutX(hexagon.getLayoutX()+deltaX);
                hexagon.setLayoutY(hexagon.getLayoutY()+deltaY);
                mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
            }
        }
    });
        
        return hexagon;
    }
    
    private Polygon createSettlement(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, Color color){
        Polygon settlement = new Polygon();
        settlement.getPoints().addAll(new Double[]{
            x1, y1,
            x2, y2,
            x3, y3,
            x4, y4,
            x5, y5,
        });
        settlement.setStroke(Color.BLACK);
        settlement.setStrokeWidth(3);
        settlement.setFill(color);
        settlement.setCursor(Cursor.HAND);
        
        final ObjectProperty<Point2D> mousePosition = new SimpleObjectProperty<>();

    settlement.setOnMousePressed(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
            settlement.toFront();
        }
    });

    settlement.setOnMouseDragged(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            double deltaX = event.getSceneX() - mousePosition.get().getX();
            double deltaY = event.getSceneY() - mousePosition.get().getY();
            settlement.setLayoutX(settlement.getLayoutX()+deltaX);
            settlement.setLayoutY(settlement.getLayoutY()+deltaY);
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
        }
    });
        
        return settlement;
    }
    
    private Polygon createCity(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, double x7, double y7, Color color){
        Polygon city = new Polygon();
        city.getPoints().addAll(new Double[]{
            x1, y1,
            x2, y2,
            x3, y3,
            x4, y4,
            x5, y5,
            x6, y6,
            x7, y7,
        });
        city.setStroke(Color.BLACK);
        city.setStrokeWidth(3);
        city.setFill(color);
        city.setCursor(Cursor.HAND);
        
        final ObjectProperty<Point2D> mousePosition = new SimpleObjectProperty<>();

    city.setOnMousePressed(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
            city.toFront();
        }
    });

    city.setOnMouseDragged(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            double deltaX = event.getSceneX() - mousePosition.get().getX();
            double deltaY = event.getSceneY() - mousePosition.get().getY();
            city.setLayoutX(city.getLayoutX()+deltaX);
            city.setLayoutY(city.getLayoutY()+deltaY);
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
        }
    });
        
        return city;
    }
    
    private Polygon createRoad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, Color color){
        Polygon road = new Polygon();
        road.getPoints().addAll(new Double[]{
            x1, y1,
            x2, y2,
            x3, y3,
            x4, y4,
        });
        road.setStroke(Color.BLACK);
        road.setStrokeWidth(3);
        road.setFill(color);
        road.setCursor(Cursor.HAND);
        
        final ObjectProperty<Point2D> mousePosition = new SimpleObjectProperty<>();

    road.setOnMouseClicked(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            if(event.isShiftDown())
                road.getTransforms().add(new Rotate(30,x1,y1));
            road.toFront();
        }
    });    
        
    road.setOnMousePressed(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
            road.toFront();
        }
    });

    road.setOnMouseDragged(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            double deltaX = event.getSceneX() - mousePosition.get().getX();
            double deltaY = event.getSceneY() - mousePosition.get().getY();
            road.setLayoutX(road.getLayoutX()+deltaX);
            road.setLayoutY(road.getLayoutY()+deltaY);
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
        }
    });
        
        return road;
    }
    
    private Circle createRobber(double x, double y, double r, Color color){
        Circle robber = new Circle(x,y,r,color);
        robber.setStroke(Color.BLACK);
        robber.setStrokeWidth(3);
        robber.setCursor(Cursor.HAND);
        
        final ObjectProperty<Point2D> mousePosition = new SimpleObjectProperty<>();
        
        robber.setOnMousePressed(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
            robber.toFront();
        }
    });

    robber.setOnMouseDragged(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            double deltaX = event.getSceneX() - mousePosition.get().getX();
            double deltaY = event.getSceneY() - mousePosition.get().getY();
            robber.setLayoutX(robber.getLayoutX()+deltaX);
            robber.setLayoutY(robber.getLayoutY()+deltaY);
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
        }
    });
        
        return robber;
    }
    
    private Circle createResource(double x, double y, double r, String type){
        Circle resource = new Circle(x,y,r);
        resource.setStroke(Color.GOLDENROD);
        resource.setStrokeWidth(5);
        resource.setCursor(Cursor.HAND);
        
        if(type=="Grain")
        {
            resource.setFill(Color.YELLOW);
        }
        else if(type=="Lumber")
        {
            resource.setFill(Color.GREEN);
        }
        else if(type=="Wool")
        {
            resource.setFill(Color.WHITE);
        }
        else if(type=="Ore")
        {
            resource.setFill(Color.GRAY);
        }
        else if(type=="Brick")
        {
            resource.setFill(Color.FIREBRICK);
        }
        else
            resource.setFill(Color.TRANSPARENT);
        
        final ObjectProperty<Point2D> mousePosition = new SimpleObjectProperty<>();
        
        resource.setOnMouseClicked(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            if(event.isShiftDown())
            {
                Paint currentcolor = resource.getFill();
                if(currentcolor==Color.GOLDENROD)
                {
                    if(type=="Grain")
                    {
                        resource.setFill(Color.YELLOW);
                    }
                    else if(type=="Lumber")
                    {
                        resource.setFill(Color.GREEN);
                    }
                    else if(type=="Wool")
                    {
                        resource.setFill(Color.WHITE);
                    }
                    else if(type=="Ore")
                    {
                        resource.setFill(Color.GRAY);
                    }
                    else if(type=="Brick")
                    {
                        resource.setFill(Color.FIREBRICK);
                    }
                    else
                    resource.setFill(Color.TRANSPARENT);
                }
                else
                    resource.setFill(Color.GOLDENROD);
            }
            
            resource.toFront();
        }
    });
        
        resource.setOnMousePressed(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
            resource.toFront();
        }
    });

    resource.setOnMouseDragged(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            double deltaX = event.getSceneX() - mousePosition.get().getX();
            double deltaY = event.getSceneY() - mousePosition.get().getY();
            resource.setLayoutX(resource.getLayoutX()+deltaX);
            resource.setLayoutY(resource.getLayoutY()+deltaY);
            mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
        }
    });
        
        return resource;
    }
    
    private Text createNumberToken(double x, double y, int num){
        
        Text numbertoken = new Text(x, y, Integer.toString(num));
        numbertoken.setFont(Font.font(null, FontWeight.BOLD, 36));
        numbertoken.setCursor(Cursor.HAND);
        
        final ObjectProperty<Point2D> mousePosition = new SimpleObjectProperty<>();
        
        numbertoken.setOnMousePressed(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            if(event.isControlDown()){
                mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
                numbertoken.toFront();
            }
        }
    });

    numbertoken.setOnMouseDragged(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            if(event.isControlDown()){
                double deltaX = event.getSceneX() - mousePosition.get().getX();
                double deltaY = event.getSceneY() - mousePosition.get().getY();
                numbertoken.setLayoutX(numbertoken.getLayoutX()+deltaX);
                numbertoken.setLayoutY(numbertoken.getLayoutY()+deltaY);
                mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
            }
        }
    });
        
        return numbertoken;
    }
    
    private Text createHarbor(double x, double y, int num1, int num2, String harbortype){
        
        Text harbor = new Text(x, y, Integer.toString(num1)+":"+Integer.toString(num2)+" "+harbortype);
        harbor.setFont(Font.font(null, FontWeight.BOLD, 20));
        harbor.setCursor(Cursor.HAND);
        
        final ObjectProperty<Point2D> mousePosition = new SimpleObjectProperty<>();
        
        harbor.setOnMouseClicked(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            if(event.isShiftDown())
                harbor.getTransforms().add(new Rotate(30,x,y));
            harbor.toFront();
        }
    });
        
        harbor.setOnMousePressed(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            if(event.isControlDown()){
                mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
                harbor.toFront();
            }
        }
    });

    harbor.setOnMouseDragged(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            if(event.isControlDown()){
                double deltaX = event.getSceneX() - mousePosition.get().getX();
                double deltaY = event.getSceneY() - mousePosition.get().getY();
                harbor.setLayoutX(harbor.getLayoutX()+deltaX);
                harbor.setLayoutY(harbor.getLayoutY()+deltaY);
                mousePosition.set(new Point2D.Double(event.getSceneX(), event.getSceneY()));
            }
        }
    });
        
        return harbor;
    }
    
    @Override
    public void start(Stage primaryStage) {
        
        Pane root = new Pane();
        
        int numField = 4;
        int numForest = 4;
        int numPasture = 4;
        int numMountain = 3;
        int numHill = 3;
        int numDesert = 1;
        
        int num2tok = 1;
        int num3tok = 2;
        int num4tok = 2;
        int num5tok = 2;
        int num6tok = 2;
        int num7tok = 0;
        int num8tok = 2;
        int num9tok = 2;
        int num10tok = 2;
        int num11tok = 2;
        int num12tok = 1;
        
        int numWHar = 1;
        int numLHar = 1;
        int numBHar = 1;
        int numOHar = 1;
        int numGHar = 1;
        int numXHar = 4;
        
        int numResource = 19;
        
        int numSettlement = 5;
        int numCity = 4;
        int numRoad = 15;
        
        double tilex1 = 100, tiley1 = 25;
        double tilex2 = 150, tiley2 = 50;
        double tilex3 = 150, tiley3 = 100;
        double tilex4 = 100, tiley4 = 125;
        double tilex5 = 50, tiley5 = 100;
        double tilex6 = 50, tiley6 = 50;
        int increm = 15;
        
        double tokx = 50 ,toky = 200;
        
        double harx = 50, hary = 250;
        
        double robx = 75, roby = 300;
        
        //creates main panel
        Polygon background = new Polygon();
        background.getPoints().addAll(new Double[]{
            0.0, 0.0,
            1000.0, 0.0,
            1000.0, 750.0,
            0.0, 750.0,
        });
        background.setStroke(Color.BLACK);
        background.setStrokeWidth(5);
        background.setFill(Color.LIGHTBLUE);
        root.getChildren().add(background);
        
        //create bank panel
        Polygon bank = new Polygon();
        bank.getPoints().addAll(new Double[]{
            0.0, 750.0,
            1000.0, 750.0,
            1000.0, 850.0,
            0.0, 850.0,
        });
        bank.setStroke(Color.BLACK);
        bank.setStrokeWidth(5);
        bank.setFill(Color.TAN);
        root.getChildren().add(bank);
        
        //create player1 panel
        Polygon player1 = new Polygon();
        player1.getPoints().addAll(new Double[]{
            0.0+2.5, 850.0+2.5,
            250.0-2.5, 850.0+2.5,
            250.0-2.5, 1000.0-2.5,
            0.0+2.5, 1000.0-2.5,
        });
        player1.setStroke(Color.RED);
        player1.setStrokeWidth(5);
        player1.setFill(Color.WHITE);
        root.getChildren().add(player1);
        
        //create player2 panel
        Polygon player2 = new Polygon();
        player2.getPoints().addAll(new Double[]{
            250.0+2.5, 850.0+2.5,
            500.0-2.5, 850.0+2.5,
            500.0-2.5, 1000.0-2.5,
            250.0+2.5, 1000.0-2.5,
        });
        player2.setStroke(Color.BLUE);
        player2.setStrokeWidth(5);
        player2.setFill(Color.WHITE);
        root.getChildren().add(player2);
        
        //create player3 panel
        Polygon player3 = new Polygon();
        player3.getPoints().addAll(new Double[]{
            500.0+2.5, 850.0+2.5,
            750.0-2.5, 850.0+2.5,
            750.0-2.5, 1000.0-2.5,
            500.0+2.5, 1000.0-2.5,
        });
        player3.setStroke(Color.BLACK);
        player3.setStrokeWidth(5);
        player3.setFill(Color.WHITE);
        root.getChildren().add(player3);
        
        //create player4 panel
        Polygon player4 = new Polygon();
        player4.getPoints().addAll(new Double[]{
            750.0+2.5, 850.0+2.5,
            1000.0-2.5, 850.0+2.5,
            1000.0-2.5, 1000.0-2.5,
            750.0+2.5, 1000.0-2.5,
        });
        player4.setStroke(Color.ORANGE);
        player4.setStrokeWidth(5);
        player4.setFill(Color.WHITE);
        root.getChildren().add(player4);
        
        //create terrain hexes
        for(int i = 0; i < numField + numForest + numPasture + numMountain + numHill + numDesert; i++)
        {
            if(i<numField)
            {
                Polygon hex = createHexagon(tilex1 + i*increm, tiley1, tilex2 + i*increm, tiley2, tilex3 + i*increm, tiley3, tilex4 + i*increm, tiley4, tilex5 + i*increm, tiley5, tilex6 + i*increm, tiley6, Color.YELLOW);
                root.getChildren().add(hex);
            }
            
            else if(i>=numField&&i<numField+numForest)
            {
                Polygon hex = createHexagon(tilex1 + i*increm, tiley1, tilex2 + i*increm, tiley2, tilex3 + i*increm, tiley3, tilex4 + i*increm, tiley4, tilex5 + i*increm, tiley5, tilex6 + i*increm, tiley6, Color.GREEN);
                root.getChildren().add(hex);
            }
            else if(i>=numField+numForest&&i<numField+numForest+numPasture)
            {
                Polygon hex = createHexagon(tilex1 + i*increm, tiley1, tilex2 + i*increm, tiley2, tilex3 + i*increm, tiley3, tilex4 + i*increm, tiley4, tilex5 + i*increm, tiley5, tilex6 + i*increm, tiley6, Color.WHITE);
                root.getChildren().add(hex);
            }
            else if(i>=numField+numForest+numPasture&&i<numField+numForest+numPasture+numMountain)
            {
                Polygon hex = createHexagon(tilex1 + i*increm, tiley1, tilex2 + i*increm, tiley2, tilex3 + i*increm, tiley3, tilex4 + i*increm, tiley4, tilex5 + i*increm, tiley5, tilex6 + i*increm, tiley6, Color.GRAY);
                root.getChildren().add(hex);
            }
            else if(i>=numField+numForest+numPasture+numMountain&&i<numField+numForest+numPasture+numMountain+numHill)
            {
                Polygon hex = createHexagon(tilex1 + i*increm, tiley1, tilex2 + i*increm, tiley2, tilex3 + i*increm, tiley3, tilex4 + i*increm, tiley4, tilex5 + i*increm, tiley5, tilex6 + i*increm, tiley6, Color.FIREBRICK);
                root.getChildren().add(hex);
            }
            else if(i>=numField+numForest+numPasture+numMountain+numHill&&i<numField+numForest+numPasture+numMountain+numHill+numDesert)
            {
                Polygon hex = createHexagon(tilex1 + i*increm, tiley1, tilex2 + i*increm, tiley2, tilex3 + i*increm, tiley3, tilex4 + i*increm, tiley4, tilex5 + i*increm, tiley5, tilex6 + i*increm, tiley6, Color.TAN);
                root.getChildren().add(hex);
            }
        }
        
        //create number tokens
        for(int i = 0; i < num2tok+num3tok+num4tok+num5tok+num6tok+num7tok+num8tok+num9tok+num10tok+num11tok+num12tok; i++)
        {
            if(i<num2tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 2);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok&&i<num2tok+num3tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 3);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok+num3tok&&i<num2tok+num3tok+num4tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 4);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok+num3tok+num4tok&&i<num2tok+num3tok+num4tok+num5tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 5);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok+num3tok+num4tok+num5tok&&i<num2tok+num3tok+num4tok+num5tok+num6tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 6);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok+num3tok+num4tok+num5tok+num6tok&&i<num2tok+num3tok+num4tok+num5tok+num6tok+num7tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 7);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok+num3tok+num4tok+num5tok+num6tok+num7tok&&i<num2tok+num3tok+num4tok+num5tok+num6tok+num7tok+num8tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 8);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok+num3tok+num4tok+num5tok+num6tok+num7tok+num8tok&&i<num2tok+num3tok+num4tok+num5tok+num6tok+num7tok+num8tok+num9tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 9);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok+num3tok+num4tok+num5tok+num6tok+num7tok&&i<num2tok+num3tok+num4tok+num5tok+num6tok+num7tok+num8tok+num9tok+num10tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 10);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok+num3tok+num4tok+num5tok+num6tok+num7tok+num8tok+num9tok+num10tok&&i<num2tok+num3tok+num4tok+num5tok+num6tok+num7tok+num8tok+num9tok+num10tok+num11tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 11);
                root.getChildren().add(tok);
            }
            else if(i>=num2tok+num3tok+num4tok+num5tok+num6tok+num7tok+num8tok+num9tok+num10tok+num11tok&&i<num2tok+num3tok+num4tok+num5tok+num6tok+num7tok+num8tok+num9tok+num10tok+num11tok+num12tok)
            {
                Text tok = createNumberToken(tokx+ i * increm, toky, 12);
                root.getChildren().add(tok);
            }
        }
        
        //create harbor pieces
        for(int i = 0; i<numWHar+numLHar+numBHar+numOHar+numGHar+numXHar; i++)
        {
            if(i<numWHar)
            {
                Text har = createHarbor(harx+i*increm, hary, 2, 1, "Wool");
                root.getChildren().add(har);
            }
            else if(i>=numWHar&&i<numWHar+numLHar)
            {
                Text har = createHarbor(harx+i*increm, hary, 2, 1, "Lumber");
                root.getChildren().add(har);
            }
            else if(i>=numWHar+numLHar&&i<numWHar+numLHar+numBHar)
            {
                Text har = createHarbor(harx+i*increm, hary, 2, 1, "Brick");
                root.getChildren().add(har);
            }
            else if(i>=numWHar+numLHar+numBHar&&i<numWHar+numLHar+numBHar+numOHar)
            {
                Text har = createHarbor(harx+i*increm, hary, 2, 1, "Ore");
                root.getChildren().add(har);
            }
            else if(i>=numWHar+numLHar+numBHar+numOHar&&i<numWHar+numLHar+numBHar+numOHar+numGHar)
            {
                Text har = createHarbor(harx+i*increm, hary, 2, 1, "Grain");
                root.getChildren().add(har);
            }
            else if(i>=numWHar+numLHar+numBHar+numOHar+numGHar&&i<numWHar+numLHar+numBHar+numOHar+numGHar+numXHar)
            {
                Text har = createHarbor(harx+i*increm, hary, 3, 1, "Generic");
                root.getChildren().add(har);
            }
        }
        
        //create robber
        Circle rob = createRobber(robx, roby, 25, Color.SLATEGRAY);
        root.getChildren().add(rob);
        
        //create settlements
        for(int i = 0; i < numSettlement; i++)
        {
            Polygon set = createSettlement(30, 900, 30, 880, 45, 870, 60, 880, 60, 900, Color.RED);
            root.getChildren().add(set);
        }
        for(int i = 0; i < numSettlement; i++)
        {
            Polygon set = createSettlement(30+250, 900, 30+250, 880, 45+250, 870, 60+250, 880, 60+250, 900, Color.BLUE);
            root.getChildren().add(set);
        }
        for(int i = 0; i < numSettlement; i++)
        {
            Polygon set = createSettlement(30+500, 900, 30+500, 880, 45+500, 870, 60+500, 880, 60+500, 900, Color.WHITE);
            root.getChildren().add(set);
        }
        for(int i = 0; i < numSettlement; i++)
        {
            Polygon set = createSettlement(30+750, 900, 30+750, 880, 45+750, 870, 60+750, 880, 60+750, 900, Color.ORANGE);
            root.getChildren().add(set);
        }
        
        //create cities
        for(int i = 0; i < numCity; i++)
        {
            Polygon city = createCity(30, 950, 30, 920, 45, 910, 60, 920, 60, 930, 70, 930, 70, 950, Color.RED);
            root.getChildren().add(city);
        }
        for(int i = 0; i < numCity; i++)
        {
            Polygon city = createCity(30+250, 950, 30+250, 920, 45+250, 910, 60+250, 920, 60+250, 930, 70+250, 930, 70+250, 950, Color.BLUE);
            root.getChildren().add(city);
        }
        for(int i = 0; i < numCity; i++)
        {
            Polygon city = createCity(30+500, 950, 30+500, 920, 45+500, 910, 60+500, 920, 60+500, 930, 70+500, 930, 70+500, 950, Color.WHITE);
            root.getChildren().add(city);
        }
        for(int i = 0; i < numCity; i++)
        {
            Polygon city = createCity(30+750, 950, 30+750, 920, 45+750, 910, 60+750, 920, 60+750, 930, 70+750, 930, 70+750, 950, Color.ORANGE);
            root.getChildren().add(city);
        }
        
        //create roads
        for(int i = 0; i < numRoad; i++)
        {
            Polygon road = createRoad(30, 980, 30, 970, 70, 970, 70, 980, Color.RED);
            root.getChildren().add(road);
        }
        for(int i = 0; i < numRoad; i++)
        {
            Polygon road = createRoad(30+250, 980, 30+250, 970, 70+250, 970, 70+250, 980, Color.BLUE);
            root.getChildren().add(road);
        }
        for(int i = 0; i < numRoad; i++)
        {
            Polygon road = createRoad(30+500, 980, 30+500, 970, 70+500, 970, 70+500, 980, Color.WHITE);
            root.getChildren().add(road);
        }
        for(int i = 0; i < numRoad; i++)
        {
            Polygon road = createRoad(30+750, 980, 30+750, 970, 70+750, 970, 70+750, 980, Color.ORANGE);
            root.getChildren().add(road);
        }
        
        //create resource tokens
        for(int i = 0; i < numResource; i++)
        {
            Circle res = createResource(50, 800, 20, "Grain");
            root.getChildren().add(res);
        }
        for(int i = 0; i < numResource; i++)
        {
            Circle res = createResource(50+50, 800, 20, "Lumber");
            root.getChildren().add(res);
        }
        for(int i = 0; i < numResource; i++)
        {
            Circle res = createResource(50+100, 800, 20, "Wool");
            root.getChildren().add(res);
        }
        for(int i = 0; i < numResource; i++)
        {
            Circle res = createResource(50+150, 800, 20, "Ore");
            root.getChildren().add(res);
        }
        for(int i = 0; i < numResource; i++)
        {
            Circle res = createResource(50+200, 800, 20, "Brick");
            root.getChildren().add(res);
        }
        
        //create dicebox background panel
        Polygon dicebox = new Polygon();
        dicebox.getPoints().addAll(new Double[]{
            750.0, 850.0,
            750.0, 750.0,
            1000.0, 750.0,
            1000.0, 850.0,
        });
        dicebox.setStroke(Color.BLACK);
        dicebox.setStrokeWidth(5);
        dicebox.setFill(Color.TAN);
        root.getChildren().add(dicebox);
        
        //create d1
        Polygon d1 = new Polygon();
        d1.getPoints().addAll(new Double[]{
            775.0, 775.0,
            825.0, 775.0,
            825.0, 825.0,
            775.0, 825.0,
        });
        d1.setStroke(Color.BLACK);
        d1.setStrokeWidth(3);
        d1.setFill(Color.WHITE);
        root.getChildren().add(d1);
        
        //create d2
        Polygon d2 = new Polygon();
        d2.getPoints().addAll(new Double[]{
            775.0+75, 775.0,
            825.0+75, 775.0,
            825.0+75, 825.0,
            775.0+75, 825.0,
        });
        d2.setStroke(Color.BLACK);
        d2.setStrokeWidth(3);
        d2.setFill(Color.WHITE);
        root.getChildren().add(d2);
        
        //create d3
        Polygon d3 = new Polygon();
        d3.getPoints().addAll(new Double[]{
            775.0+150, 775.0,
            825.0+150, 775.0,
            825.0+150, 825.0,
            775.0+150, 825.0,
        });
        d3.setStroke(Color.BLACK);
        d3.setStrokeWidth(3);
        d3.setFill(Color.WHITE);
        root.getChildren().add(d3);
        
        //+
        Text plus = new Text(826, 810, "+");
        plus.setFont(Font.font(null, FontWeight.BOLD, 30));
        root.getChildren().add(plus);
        
        //=
        Text equal = new Text(901, 810, "=");
        equal.setFont(Font.font(null, FontWeight.BOLD, 30));
        root.getChildren().add(equal);
        
        //dice label 1
        Text dnum1 = new Text(788, 815, Integer.toString(0));
        dnum1.setFont(Font.font(null,FontWeight.BOLD, 40));
        root.getChildren().add(dnum1);
        
        //dice label 2
        Text dnum2 = new Text(788+75, 815, Integer.toString(0));
        dnum2.setFont(Font.font(null,FontWeight.BOLD, 40));
        root.getChildren().add(dnum2);
        
        //dice label sum
        Text dnum3 = new Text(788+150, 815, Integer.toString(0));
        dnum3.setFont(Font.font(null,FontWeight.BOLD, 40));
        root.getChildren().add(dnum3);
        
        //transparent clickable dice roller
        Polygon diceroller = new Polygon();
        diceroller.getPoints().addAll(new Double[]{
            750.0, 850.0,
            750.0, 750.0,
            1000.0, 750.0,
            1000.0, 850.0,
        });
        diceroller.setStroke(Color.BLACK);
        diceroller.setStrokeWidth(5);
        diceroller.setFill(Color.TRANSPARENT);
        diceroller.setCursor(Cursor.HAND);
        root.getChildren().add(diceroller);
        
        diceroller.setOnMouseClicked(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
            int rollnum1 = (int)(Math.random() * ((6 - 1)+1))+1; 
            int rollnum2 = (int)(Math.random() * ((6 - 1)+1))+1;
            
            dnum1.setText(Integer.toString(rollnum1));
            dnum2.setText(Integer.toString(rollnum2));
            dnum3.setText(Integer.toString(rollnum1+rollnum2));
            
            if (rollnum1 + rollnum2 == 7)
            {
                dnum3.setFill(Color.RED);
            }
            else
                dnum3.setFill(Color.BLACK);
            
            if (dnum3.getText().length()>1)
            {
                dnum3.setX(928);
            }
            else
                dnum3.setX(938);
        }
    });
        
        //create some help text
        Text help = new Text(300, 790, "Left MB + Ctrl = Move Terrain Hexes, Harbor Pieces, and Number Tokens\nLeft MB + Shift = Rotate Roads and Harbor Pieces and Hide Resource Tokens\nClick on \"Settlers of Catan\" for full rules!");
        root.getChildren().add(help);
        
        //create build cost
        Text build = new Text(5, 680, "-=BUILDING COSTS=-\n1 Brick + 1 Lumber = Road\n1 Brick + 1 Lumber + 1 Grain + 1 Wool = Settlement\n2 Grain + 3 Ore = City\n1 Wool + 1 Grain + 1 Ore = Development Card (Not Included)");
        build.setFont(Font.font(null, FontWeight.BOLD, 12));
        root.getChildren().add(build);
        
        //create title
        Text title = new Text(5, 20, "Settlers Of Catan");
        title.setFont(Font.font(null, FontWeight.BOLD, 20));
        root.getChildren().add(title);
        //title.setFill(Color.RED);
        title.setCursor(Cursor.HAND);
        
        title.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                
                File file = new File("D:/Lucas Kehoe - Final Project/catan_5th_ed_rules_eng_150303.pdf");
                HostServices hostservices = getHostServices();
                hostservices.showDocument(file.getAbsolutePath());
                
            }
        });
        
        Scene scene = new Scene(root, 990, 990);
        
        primaryStage.setTitle("CS344 Settlers of Catan");
        primaryStage.setResizable(false);
        primaryStage.setScene(scene);
        primaryStage.show();
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }

    
}