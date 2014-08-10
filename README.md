wordstat
========

Word stat program used to print each unique word, along with number of occurrences (case sensitive and non-case sensitive)

The data structure I used for this assignment is a linked list of linked lists.
for each different word, I create a lowercase version of that word and use it as a "header" node.
Each header node has an int called num that stores the number of times a word has occured, and a csnum which stores the
number of case sensitive versions of a word.
In main, I loop through the inputted text file by character, and add the characters to a char* called str appropriately.
The word will be composed of digits and letters, and after it is created, sent to another function called chopdigits.
This removes the potential digits from the beginning of a word, as a word cannot start with digits.
If n is the number of words, this part of the program has an efficiency of O(n),
as it only needs to loop once to find all of the words and send them to be put in the linked lists.
In terms of memory, if n is the number of characters and each character takes 1 byte of memory, this function will take n bytes.
After a word has successfully been created, I send it to the processStr function.
As the words come into processStr, if their lower case version matches a previously created "header" node,
I increase the header node's count by 1.
As I traverse down to place it at the end of the list, I check to see if the word's case sensitive version number should change, a    nd increase it appropriately.
Each word has its own node, and each node has a character array for space of the entire file (incase the file is just one word), a    n int num, int csnum,
a pointer to a node next, a pointer to another node neighbor,
and a pointer to a third node prevneighbor. thus the space for the entire list of nodes (if n = number of words in file, and c is     the number of characters)
is respectively n(c + 8 + 3n).
If a word is sent to processStr and there are no matching words in the data structure, I start from the head node,
and traverse down the "header" nodes until I reach one that is lexicographically less than the word sent to processStr.
Then, I create a new "header" node for this word, and place it before that node in the linked list. Then I add the case-sensitive     node to this header node.
This keeps the word in lexicographical order, which makes printing the words at the end much easier.
The worst case for this method is an O(n^2), which occurs with a file that has words that are already sorted,
and contains all unique words.
