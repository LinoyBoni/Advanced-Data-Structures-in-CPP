/*Yael Otmazgin 212531115
Linoy Bony 211820824
Exercise 03*/
#include "Book.h"
#include "Trie.h"
#include <algorithm>
#include <string>
#include <regex>
#include <list>

using namespace std;
// Constructor that reads the content of a file and initializes the Trie
Book::Book(const string& filepath)
{
    // Open the file at the specified filepath
    ifstream file(filepath);

    // Check if the file is successfully opened
    if (file.is_open())
    {
        // Read the entire content of the file into a stringstream
        stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
        file.close();

        // Transform the content to lowercase
        transform(content.begin(), content.end(), content.begin(), ::tolower);

        // Replace consecutive whitespaces with a single space using regular expressions
        regex pattern("\\s+"); // Matches one or more whitespace characters
        content = regex_replace(content, pattern, " ");

        // Insert content into the trie
        processContent();
    }
    else
    {
        // If the file fails to open, throw an exception
        throw invalid_argument("Unable to open file");
    }
}
// Private method to process the content of the book
void Book::processContent()
{
    istringstream stream(content);
    // TODO: Go over the book content and add any triplet of consecutive words to the trie.
    // Assume the words are separated by spaces.
    string currentWord, nextWord, nextNextWord, word;
    stream >> currentWord >> nextWord; // Read the first 3 words of the text
    int index = 0;
    while (stream >> nextNextWord)
    {
        word = currentWord + " " + nextWord + " " + nextNextWord;
        trie.insert(index, word); // Insert the 3 words into the trie
        index += currentWord.size() + 1;
        currentWord = nextWord;
        nextWord = nextNextWord;
    }
}
// Method to search for sentences containing a query and print them
void Book::searchAndPrint(const string& query)
{
    // TODO: Use the trie to find the locations of the string (At most 3 sentences)
    // TODO: For each location, use the extractSentence function to extract the sentence in that location
    // TODO: Print each sentence
    list<int> locations = trie.search(query);// TODO: fix
    if (locations.empty()) {
        cout << "No results" << endl;
    }
    else {
        cout << "Sentences matching the prefix:" << endl;
        int count = 0;
        for (int loc : locations) {
            if (count >= 3) break;
            string sentence = extractSentence(loc);
            cout << sentence << endl;
            count++;
        }
    }
}
// Method to extract a sentence surrounding a given location
string Book::extractSentence(int location)
{
    // TODO: Go over the characters of the content from the location backwards until finding a '.' or until accumulating 5 words.
    // TODO: Go over the characters of the content from the location forwards until finding a '.' or until accumulating a total of 10 words.
    // TODO: Assemble the sentence by adding the two parts with a '*' marker for the location and '...' if the sentence was cut.
    int counterWordsStart = 0;
    int i;
    for (i = location - 2; counterWordsStart < 5 && i >= 0; i--)
    {
        if (content[i] == ' ')
            counterWordsStart++;
        if (content[i] == '.')
            break;
    }
    int startPos = i + 1;

    int counterWordsEnd = 0;

    for (i = location; counterWordsEnd < 10 - counterWordsStart && i < content.size(); i++)
    {
        if (content[i] == ' ')
            counterWordsEnd++;
        if (content[i] == '.')
        {
            counterWordsEnd++;
            break;
        }
    }
    int endPos = i - 1;
    if (content[endPos] == ' ')
        endPos--;

    string str = "";

    if (startPos > 1 && content[startPos - 1] != '.')
        str += "...";

    if (startPos == 0)
        startPos--;
    str.append(content, startPos + 1, location - startPos - 1);
    str += "*";
    str.append(content, location, endPos - location + 1);

    if (endPos != content.size() - 1)
    {
        if (content[endPos + 1] != '.')
            str += "...";
        else
            str += '.';
    }

    return str;
}
// Method to censor occurrences of a query in the book
void Book::censorQuery(const string& query)
{
    //TODO: remove the query from the trie (mark it as a non end-of-word)
    trie.remove(query);
}