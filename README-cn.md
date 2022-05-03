<h1 align="center">化学配平器</h1>
<p align="center">
  <a href="./README.md">English</a> |
  <a>中文</a> 
</p>
<p align="center">
  <img src="https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white" />
  <img src="https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white" />
  <img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" />
  <img src="https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge" />
</p>

## 简介

 - 本程序可实现化学、离子方程式的配平和检测是否配平
 - 输入的化学方程式规则如下：

```
  <equation> ::= <expr> "=" <expr>
  <expr> ::= <coef> <formula> | <expr> "+" <coef> <formula>
  <coef> ::= <digits> | "" | <electron>
  <electron>::= "<"<digits>"+>" | "<"<digits>"->" | ""
  <digits> ::= {<digit>} 
  <digit> ::= "0" | "1" | ... | "9"
  <formula> ::= <term> <coef> | <formula> <term> <coef>
  <term> ::= <element> | "(" <formula> ")" |  "[" <formula> "]"
  <element> ::= <uppercase> | <uppercase> <lowercase>
  <uppercase> ::= "A" | "B" | ... | "Z"
  <lowercase> ::= "a" | "b" | ... | "z"
```
## 应用
 - [下载](https://github.com/AMT-J/Chemical-Balancer/releases/tag/v5.2.0)
