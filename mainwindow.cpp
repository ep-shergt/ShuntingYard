#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <string.h>
#include <string>
#include <iostream>
#include <iterator>
#include <stack>
#include <sstream>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

using namespace std;
QString infix;
QByteArray ba;
QString postfix;
QString Qstack;
bool TryParse(const string &symbol);
int Priority(const string &c);
bool isOperator(const string &c);
char *infixneu;
string s_infix = "";
string s_postfix = "";
QString error;



void MainWindow::on_btn_convert_clicked()
{
    ui->txt_postfix->clear();
    infix = ui->txt_infix->toPlainText();
    s_infix = infix.toStdString();


    // Shunting Yard Algorithm
    //s_infix = "3 ^ 4 + ( 11 - ( 3 * 2 ) ) / 2";
    istringstream iss(s_infix);
    vector<string> tokens;
    while(iss) {
        string temp;
        iss >>temp;
        tokens.push_back(temp);
    }

    vector<string> outputList;
    stack<string> s;
    for(unsigned int i = 0; i < tokens.size(); i++)  //read from right to left
        {
            if(TryParse(tokens[i]))
            {
                outputList.push_back(tokens[i]);
            }
            if(tokens[i] == "(")
            {
                s.push(tokens[i]);
            }
            if(tokens[i] == ")")
            {
                while(!s.empty() && s.top() != "(")
                {
                    outputList.push_back(s.top());
                    s.pop();
                }
                s.pop();
            }
            if(isOperator(tokens[i]) == true)
            {
                while(!s.empty() && Priority(s.top()) >= Priority(tokens[i]))
                {
                    outputList.push_back(s.top());
                    s.pop();
                }
                s.push(tokens[i]);
            }
        }
        //pop any remaining operators from the stack and insert to outputlist
        while(!s.empty())
        {
            outputList.push_back(s.top());
            s.pop();
        }
    for (unsigned int j = 0; j < outputList.size(); j++) {
        s_postfix = s_postfix + outputList[j] + " ";
    }

    Qstack = QString::fromStdString(s_postfix);
    postfix.push_back(Qstack);
    ui->txt_postfix->setText(postfix);
    outputList.clear();
    postfix = "";
}

bool TryParse(const string &symbol) {
    bool isNumber = false;
    for (unsigned int i = 0; i < symbol.size(); i++) {
        if(!isdigit(symbol[i])) {
            isNumber = false;
        } else {
            isNumber = true;
        }
    }
    return isNumber;
}

int Priority(const string &c) {
    if(c == "^") {
        return 3;
    }
    if(c == "*" || c == "/") {
        return 2;
    }
    if(c == "+" || c == "-") {
        return 1;
    } else {
        return 0;
    }
}

bool isOperator(const string &c) {
   return (c == "+" || c == "-" || c == "*" || c == "/" || c == "^");
}
