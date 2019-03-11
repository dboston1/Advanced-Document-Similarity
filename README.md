# CS253-TermProject
This is the final version of my term project for CS253 (Fall 2017). 

It includes the following features:
* Given a document, will rank additionally provided documents by similarity and reading level
* Estimates the reading level of a document per the Coleman-Laiu index
* Computes similarity using TFIDF - Term Frequency Inverse Document Frequency (used by early web browsers)
* Performs word stemming using the Porter Algorithm 
* Is extremely efficient - without multithreading, it can compare the complete works of William Shakespeare in about 3 seconds
* Extensive error-checking (with helpful error messages printed to console).

It is written in C++. Please note this was written earlier on in my programming career, and was soley designed by me - as such, there aren't as many comments as there should be! :)

Instructions:

To compile: make 

*it will create an executable called PA9*

To run: ./PA9 file1 file2 num1 num2

*where:*
* file1: is the name of the text document against which all others should be compared 
* file2: is the name of a text document containing names of other text documents (in the same directory), each seperated by whitespace. The first filename listed in file2 is the exceptions file; its required format is listed below. The rest are the documents to be compared against file1. 
* num1: the lowest acceptable reading level (as defined by the Coleman-Laiu index)
* num2: the highest acceptable reading level (as defined by the Coleman-Laiu index)

Exceptions file format: Some words should be exempt from the word stemming. While this program does classify and ignore names, locations, etc. when performing word stemming, this allows for even greater flexibility. The correct format for this file is:

word replaceWith

word2 replaceWith2

*and so on.*

So, if you prefer the word "smiled" is changed to "smiling" (instead of being stemmed to "smile"), then your exception file would look like:

smiled smiling

Please note all document files should have a text extension (.txt). :)


