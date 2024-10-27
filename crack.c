// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "md5.h"

// const int PASS_LEN = 20;        // Maximum any password will be
// const int HASH_LEN = 33;        // Length of MD5 hash strings


// // Given a target plaintext word, use it to try to find
// // a matching hash in the hashFile.
// // Get this function working first!
// char * tryWord(char * plaintext, char * hashFilename)
// {
//     // Hash the plaintext

//     // Open the hash file

//     // Loop through the hash file, one line at a time.

//     // Attempt to match the hash from the file to the
//     // hash of the plaintext.

//     // If there is a match, you'll return the hash.
//     // If not, return NULL.

//     // Before returning, do any needed cleanup:
//     //   Close files?
//     //   Free memory?

//     // Modify this line so it returns the hash
//     // that was found, or NULL if not found.
//     return "0123456789abcdef0123456789abcdef";
// }


// int main(int argc, char *argv[])
// {
//     if (argc < 3) 
//     {
//         fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
//         exit(1);
//     }

//     // These two lines exist for testing. When you have
//     // tryWord working, it should display the hash for "hello",
//     // which is 5d41402abc4b2a76b9719d911017c592.
//     // Then you can remove these two lines and complete the rest
//     // of the main function below.
//     char *found = tryWord("hello", "hashes00.txt");
//     printf("%s %s\n", found, "hello");


//     // Open the dictionary file for reading.
    

//     // For each dictionary word, pass it to tryWord, which
//     // will attempt to match it against the hashes in the hash_file.
    
//     // If we got a match, display the hash and the word. For example:
//     //   5d41402abc4b2a76b9719d911017c592 hello
    
//     // Close the dictionary file.

//     // Display the number of hashes that were cracked.
    
//     // Free up any malloc'd memory?
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings

// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hashedPlaintext = md5(plaintext, strlen(plaintext));  // Hash the plaintext

    // Open the hash file
    FILE *hashFile = fopen(hashFilename, "r");
    if (!hashFile) {
        fprintf(stderr, "Could not open hash file: %s\n", hashFilename);
        return NULL;
    }

    char line[HASH_LEN + 1];  // Buffer to hold each line from the hash file
    // Loop through the hash file, one line at a time.
    while (fgets(line, sizeof(line), hashFile)) {
        line[strcspn(line, "\n")] = 0; // Trim newline character

        // Attempt to match the hash from the file to the
        // hash of the plaintext.
        if (strcmp(line, hashedPlaintext) == 0) {
            fclose(hashFile);
            return hashedPlaintext;  // Return the matching hash
        }
    }

    // If there is a match, you'll return the hash.
    // If not, return NULL.

    // Before returning, do any needed cleanup:
    //   Close files?
    //   Free memory?
    fclose(hashFile);
    free(hashedPlaintext); // Free allocated memory for the hash
    return NULL;  // No match found
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
    char *found = tryWord("hello", "hashes00.txt");
    printf("%s %s\n", found, "hello");

    // Open the dictionary file for reading.
    FILE *dictFile = fopen(argv[2], "r");
    if (!dictFile) {
        fprintf(stderr, "Could not open dictionary file: %s\n", argv[2]);
        exit(1);
    }

    char word[PASS_LEN + 1];  // Buffer for reading dictionary words
    int crackedCount = 0;     // Count of cracked hashes

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    while (fgets(word, sizeof(word), dictFile)) {
        word[strcspn(word, "\n")] = 0; // Trim newline character
        char *found = tryWord(word, argv[1]); // Try to crack the hash

        // If we got a match, display the hash and the word. For example:
        //   5d41402abc4b2a76b9719d911017c592 hello
        if (found != NULL) {
            printf("%s %s\n", found, word);
            crackedCount++;
        }
    }

    // Close the dictionary file.
    fclose(dictFile);

    // Display the number of hashes that were cracked.
    printf("%d hashes cracked!\n", crackedCount);

    // Free up any malloc'd memory?
    return 0; // Successful execution
}



