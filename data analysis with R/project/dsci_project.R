library(shiny)
library(tidyverse)
library(ggplot2)

lol <- read.csv("luga_lol_match_history.csv")

ui <- fluidPage(
  titlePanel("LUGA - League of Legends"),
  sidebarLayout(
    sidebarPanel(
      selectInput("selectdate",
                  label = "Date",
                  choices = sort(unique(lol$date))),
      selectInput("selectgamenumber",
                  label = "Game Number",
                  choices = sort(unique(lol$gamenumber))),
      selectInput("selectstats",
                  label = "Stats",
                  choices = list("KDA Ratio" = "kdaratio",
                                 "Kill Participation" = "killparticipation",
                                 "Damage Per Death" = "damageperdeath",
                                 "Damage Share" = "damageshare",
                                 "Damage Per Gold" = "damagepergold",
                                 "Gold Advantage" = "goldadvantage",
                                 "CS Advantage" = "csadvantage",
                                 "CS Per Minute" = "csperminute",
                                 "Kills" = "kill",
                                 "Deaths" = "death",
                                 "Assist" = "assist",
                                 "Total Damage Dealt to Champions" = "totaldamagedealttochampions",
                                 "Total Damage Dealt" = "totaldamagedealt",
                                 "Total Damage Dealt to Objectives" = "totaldamagetoobjectives",
                                 "Total Damage Dealt to Towers" = "totaldamagetoturrets",
                                 "Wards Placed" = "wardsplaced",
                                 "Wards Destroyed" = "wardsdestroyed",
                                 "Control Wards Purchased" = "controlwardspurchased",
                                 "Gold Earned" = "goldearned"
                                 ))
    ),
    mainPanel(
      plotOutput("plot1"),
      textOutput("text1"),
      textOutput("text2"),
      textOutput("text3"),
      tableOutput("table1"),
      tableOutput("table2")
    )
  )
)

server <- function(input, output) {
  output$plot1 <- renderPlot({
    df <- lol %>% 
      filter(date==input$selectdate) %>% 
      filter(gamenumber==input$selectgamenumber)
    
    ggplot(data = df, mapping=aes(x=reorder(summoner,df[[input$selectstats]]),y=df[[input$selectstats]],fill=side))+ 
      geom_bar(stat="identity", color="black")+
      labs(x="summoner",y=input$selectstats)+
      scale_fill_manual(values=c("blue","red"))+
      coord_flip()
  })
  output$text1 <- renderText({
    lolb <- lol %>% 
      filter(date==input$selectdate) %>% 
      filter(gamenumber==input$selectgamenumber) %>% 
      filter(side=="blue")
    paste("Blue Side: ", unique(lolb$team), " - ", unique(lolb$victorydefeat))
    
  })
  output$text2 <- renderText({
    lolr <- lol %>% 
      filter(date==input$selectdate) %>% 
      filter(gamenumber==input$selectgamenumber) %>% 
      filter(side=="red")
    paste("Red Side: ", unique(lolr$team), "  - ", unique(lolr$victorydefeat))
  })
  output$text3 <- renderText({
    df <- lol %>% 
      filter(date==input$selectdate) %>% 
      filter(gamenumber==input$selectgamenumber)
    paste("Match Length: ", unique(df$time))
  })
  output$table1 <- renderTable({
    df <- lol %>% 
      filter(date==input$selectdate) %>% 
      filter(gamenumber==input$selectgamenumber) %>% 
      filter(side=="blue")
    select(df,team,role:csperminute)
  })
  output$table2 <- renderTable({
    df <- lol %>% 
      filter(date==input$selectdate) %>% 
      filter(gamenumber==input$selectgamenumber) %>% 
      filter(side=="red")
    select(df,team,role:csperminute)
  })
}

shinyApp(ui = ui, server = server)