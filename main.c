#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif
#include <stdio.h>
#include "include/yaml.h"
#include <string.h>


char *replaceSlash(char *path) {
    int length = 0;
    while (path[length] != '\0') {
        length++;
    }

    char *replaced = (char *)malloc(length+1);
    int i;
    for (i = 0; path[i] != '\0'; i++) {
        if (path[i] != '\\') {
            replaced[i] = path[i];
        } else {
            replaced[i] = '/';
        }
    }
    replaced[length] = '\0';
    return replaced;
}



void printType(yaml_token_t* token) {


    switch(token->type) {
        /** An empty token. */
        case YAML_NO_TOKEN:
            printf("YAML_NO_TOKEN\n");
            break;
        case YAML_STREAM_START_TOKEN:
            printf("YAML_STREAM_START_TOKEN\n");
            break;
        case YAML_STREAM_END_TOKEN:
            printf("YAML_STREAM_END_TOKEN\n");
            break;
        case YAML_VERSION_DIRECTIVE_TOKEN:
            printf("YAML_VERSION_DIRECTIVE_TOKEN\n");
            break;
        case YAML_TAG_DIRECTIVE_TOKEN:
            printf("YAML_TAG_DIRECTIVE_TOKEN\n");
            break;
        case YAML_DOCUMENT_START_TOKEN:
            printf("YAML_DOCUMENT_START_TOKEN\n");
            break;
        case YAML_DOCUMENT_END_TOKEN:
            printf("YAML_DOCUMENT_END_TOKEN\n");
            break;
        case YAML_BLOCK_SEQUENCE_START_TOKEN:
            printf("YAML_BLOCK_SEQUENCE_START_TOKEN\n");
            break;
        case YAML_BLOCK_MAPPING_START_TOKEN:
            printf("YAML_BLOCK_MAPPING_START_TOKEN\n");
            break;
        case YAML_BLOCK_END_TOKEN:
            printf("YAML_BLOCK_END_TOKEN\n");
            break;
        case YAML_FLOW_SEQUENCE_START_TOKEN:
            printf("YAML_FLOW_SEQUENCE_START_TOKEN\n");
            break;
        case YAML_FLOW_SEQUENCE_END_TOKEN:
            printf("YAML_FLOW_SEQUENCE_END_TOKEN\n");
            break;
        case YAML_FLOW_MAPPING_START_TOKEN:
            printf("YAML_FLOW_MAPPING_START_TOKEN\n");
            break;
        case YAML_FLOW_MAPPING_END_TOKEN:
            printf("YAML_FLOW_MAPPING_END_TOKEN\n");
            break;
        case YAML_BLOCK_ENTRY_TOKEN:
            printf("YAML_BLOCK_ENTRY_TOKEN\n");
            break;
        case YAML_FLOW_ENTRY_TOKEN:
            printf("YAML_FLOW_ENTRY_TOKEN\n");
            break;
        case YAML_KEY_TOKEN:
            printf("YAML_KEY_TOKEN\n");
            break;
        case YAML_VALUE_TOKEN:
            printf("YAML_VALUE_TOKEN\n");
            break;
        case YAML_ALIAS_TOKEN:
            printf("YAML_ALIAS_TOKEN\n");
            break;
        case YAML_TAG_TOKEN:
            printf("YAML_TAG_TOKEN\n");
            break;
        case YAML_SCALAR_TOKEN:
            printf("YAML_SCALAR_TOKEN\n");
            break;
        default:
            printf("Token type: not found...\n");
            break;
    }
}




int main(int arg, char *argv[]) {
    char *paths = "paths";

    for (int i = 0; i<arg; i++) {
        printf("arg %d: %s \n", i, argv[i]);
    }

    char *xdPath = replaceSlash(argv[0]);

    char *fileName = "test.yml";
    int catLen = strlen(xdPath) +  strlen(fileName);
    char *yamlPath = (char *)malloc(catLen+1);
    FILE *fh = fopen(0, "r");
    yaml_parser_t parser;
    yaml_token_t token;

    /* Initialize parser */
    if(!yaml_parser_initialize(&parser))
        fputs("Failed to initialize parser!\n", stderr);
    if(fh == NULL)
        fputs("Failed to open file!\n", stderr);

    /* Set input file */
    yaml_parser_set_input_file(&parser, fh);

    int depth = 0;
    int found = 0;
    int argPos = 0;
    do {
        yaml_parser_scan(&parser, &token);
        printType(&token);
        // switch(token.type) {
        //     case YAML_KEY_TOKEN:
        //         printf("Key:  \t");
        //         break;
        //     case YAML_VALUE_TOKEN:
        //         printf("Value:\t");
        //         break;
        //     case YAML_SCALAR_TOKEN:
        //         printf("%s at %d \n", token.data.scalar.value, depth);
        //         // if(depth == found && strcmp((char *)token.data.scalar.value,
        //         //             args[argPos]) == 0) {
        //         //     return 1;
        //         // }
        //         break;
        //     case YAML_BLOCK_SEQUENCE_START_TOKEN:
        //         printf("Block sequence entry\n");
        //         depth++;
        //     case YAML_BLOCK_MAPPING_START_TOKEN:
        //         printf("Block mapppping entry\n");
        //         depth++;
        //     case YAML_BLOCK_ENTRY_TOKEN:
        //         printf("Block entry\n");
        //         depth++;
        //     case YAML_BLOCK_END_TOKEN:
        //         printf("BLOCK END token here\n");
        //         depth--;
        //     default:
        //         break;
        // }
        if(token.type != YAML_STREAM_END_TOKEN) {
            yaml_token_delete(&token);
        }
    } while(token.type != YAML_STREAM_END_TOKEN);
    printf("Result: %d", found);

    // Delete token
    yaml_token_delete(&token);

    /* Cleanup */
    yaml_parser_delete(&parser);
    fclose(fh);
    return 0;
}
