# PROBABILISTIC PARSER: IMPLEMENTATION OF THE EARLEY PARSER ALGORITHM WITH THE USE OF PROBABILITIES

The Earley Parser algorithm implemented in C ++ following the pseudocode of this [document](https://www.cs.unm.edu/~luger/ai-final2/CH9_Dynamic%20Programming%20and%20the%20Earley%20Parser.pdf).

## 1. Concept: 
A probability will be assigned to every production of the grammar in order to achieve optimizations.

## 2. Class Diagram
The class diagram is shown in the following image so that the structure of the project can be better understood


![Class diagram](https://github.com/Jack-Christopher/ADA-Project/blob/master/image.png)


## 3. How it works?
First you have to download the whole project, if you want you can change the content of the grammar.txt file with the grammar you desire in the Backus-Naur Form, each production must be in one separate line, if there are more than one option for a left side, each option must be separated by a space, in the next way:
    
    symbol ::= expression_1 | expression_2 | ... | expression_n
 If the expression is a nonterminal it must go between < >\
 If the expression is a terminal it must go between " "
 
 
 The Example provided in the project is the next:
 
    <S> ::= <NP> <VP>
    <NP> ::= <NP> <PP> | <Noun>
    <VP> ::= <Verb> <NP> | <VP> <PP>
    <PP> ::= <Prep> <NP>
    <Noun> ::= "john" | "mary" | "denver"
    <Verb> ::= "called" | "greet"
    <Prep> ::= "from"
 
 
Then you have to compile it in the next way: 
      
      g++ main.cpp -o main
Next, run it:
    
    ./main
You'll be asked to enter the Initial Symbol.\
The grammar entered will be displayed, each production will have a initial probability of 0.\
For each nonterminal of the grammar you must choose wheter set its probability.\
If you accept, you must enter the probability of that that nonterminal node converts into a determined production.\
The index created will be displayed.\
Finally, you'll be asked to enter a string to be analyzed by the Probabilistic Parser and the result will be displayed, this is wheter the grammar can produce that string or not.


## 4. EXTRA
(IN PROGRESS)
