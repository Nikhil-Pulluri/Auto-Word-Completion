#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked list node structure
struct node {
    char *word;
    struct node *next;
};

// Function to create a new node
struct node *new_node(char *word);

// Function to add a node to the end of a linked list
void add_to_list(struct node **head, char *word);

// Function to load words from a file into a linked list
struct node *load_dictionary(char *filename);

// Function to check if a word is in a linked list
int is_in_list(struct node *head, char *word);

// Function to free memory allocated for a linked list
void free_list(struct node *head);

// Main function
int main() {
    char a[] = "dictionary_SPELL.txt";
    struct node *head = load_dictionary(a);

    if (head == NULL) {
        printf("Could not load dictionary file.\nPlease load the file and then continue\n");
        return 1;
    }

    // Get words from user input
    char word[100];
    printf("Say Hi to our Spell Checker!!\nThis is a tool to make your content(Some sentence or paragraph) with correct spellings\n");
    printf("Please enter the sentence or paragraph\n");

    while (scanf("%s", word)) {
        // Strip newline character from end of word
        int len = strlen(word);

        if (word[len - 1] == ' ') {
            word[len - 1] = '\0';
        }

        // Converts uppercase letters to lowercase
        if (word[0] <= 90 && word[0] >= 65) {
            word[0] += 32;
        }

        if (!(word[len - 1] <= 122 && word[len - 1] >= 97)) {
            word[len - 1] = '\0';
        }

        // Check if word is in the dictionary
        if (!is_in_list(head, word)) {
            printf("'%s' is not in the dictionary word.\n", word);
        }
    }

    // Free memory
    free_list(head);
    return 0;
}

// Function to create a new node
struct node *new_node(char *word) {
    struct node *new = malloc(sizeof(struct node));
    new->word = strdup(word);
    new->next = NULL;
    return new;
}

// Function to add a node to the end of a linked list
void add_to_list(struct node **head, char *word) {
    struct node *new = new_node(word);
    struct node *current = *head;

    if (current == NULL) {
        *head = new;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

// Function to load words from a file into a linked list
struct node *load_dictionary(char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return NULL;
    }

    struct node *head = NULL;
    char word[100];

    while (fscanf(file, "%s", word) != EOF) {
        add_to_list(&head, word);
    }

    fclose(file);
    return head;
}

// Function to check if a word is in a linked list
int is_in_list(struct node *head, char *word) {
    struct node *current = head;

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

// Function to free memory allocated for a linked list
void free_list(struct node *head) {
    struct node *current = head;

    while (current != NULL) {
        struct node *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}
