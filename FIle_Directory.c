#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
// ----------------------------- STRUCTURE ----------------------------- 
struct Node { 
    char name[50]; 
    struct Node *child[10]; 
    int childCount; 
}; 
 
// ----------------------------- CREATE NODE ----------------------------- 
struct Node* createNode(char name[]) { 
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 
    strcpy(newNode->name, name); 
    newNode->childCount = 0; 
    return newNode; 
} 
 
// ----------------------------- ADD CHILD ----------------------------- 
void addChild(struct Node* parent, struct Node* child) { 
    parent->child[parent->childCount++] = child; 
} 
 
// ----------------------------- DFS USING STACK ----------------------------- 
void DFS(struct Node* root) { 
    if (root == NULL) return; 
 
    struct Node* stack[100]; 
    int top = -1; 
    stack[++top] = root; 
 
    printf("\nDFS Traversal:\n"); 
    while (top >= 0) { 
        struct Node* current = stack[top--]; 
        printf("%s\n", current->name); 
 
        // Push children in reverse order (so leftmost child is processed first) 
        for (int i = current->childCount - 1; i >= 0; i--) { 
            stack[++top] = current->child[i]; 
        } 
    } 
} 
 
// ----------------------------- BFS USING QUEUE ----------------------------- 
void BFS(struct Node* root) { 
    if (root == NULL) return; 
 
    struct Node* queue[100]; 
    int front = 0, rear = 0; 
    queue[rear++] = root; 
 
    printf("\nBFS Traversal:\n"); 
    while (front < rear) { 
        struct Node* current = queue[front++]; 
        printf("%s\n", current->name); 
 
        for (int i = 0; i < current->childCount; i++) { 
            queue[rear++] = current->child[i]; 
        } 
    } 
} 
 
// ----------------------------- MAIN FUNCTION ----------------------------- 
int main() { 
    int numFolders, numSub; 
    char folderName[50], subName[50]; 
 
    printf("Enter the name of root folder: "); 
    scanf("%s", folderName); 
    struct Node* root = createNode(folderName); 
 
    printf("\nHow many subfolders under %s? ", folderName); 
    scanf("%d", &numFolders); 
 
    for (int i = 0; i < numFolders; i++) { 
        printf("\nEnter name of subfolder %d: ", i + 1); 
        scanf("%s", subName); 
        struct Node* subFolder = createNode(subName); 
        addChild(root, subFolder); 
 
        printf("How many subfolders under %s? ", subName); 
        scanf("%d", &numSub); 
 
        for (int j = 0; j < numSub; j++) { 
            char subSubName[50]; 
            printf("Enter name of subfolder %d under %s: ", j + 1, subName); 
            scanf("%s", subSubName); 
            struct Node* subSubFolder = createNode(subSubName); 
            addChild(subFolder, subSubFolder); 
        } 
    } 
 
    DFS(root); 
    BFS(root); 
 
    return 0; 
} 