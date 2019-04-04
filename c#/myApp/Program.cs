using System;

class ReadFromFile
{
    // takes a word and returns its initial
    static char initial(string s) {             // static - method that belongs to the class (don't have to create object of that class to access it)   
                                                // Math.sqrt(for example)
        char init;
        init = s[0];
        return init;
    }
    static void Main()
    {
        string phrase = "Victor";
        int numChars = phrase.Length;              // returns # chars in string
        initial(phrase);
        Console.WriteLine();              
    }
}