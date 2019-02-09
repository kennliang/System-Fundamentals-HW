#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "huff.h"
#include "debug.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

/*
 * You may modify this file and/or move the functions contained here
 * to other source files (except for main.c) as you wish.
 *
 * IMPORTANT: You MAY NOT use any array brackets (i.e. [ and ]) and
 * you MAY NOT declare any arrays or allocate any storage with malloc().
 * The purpose of this restriction is to force you to use pointers.
 * Variables to hold the nodes of the Huffman tree and other data have
 * been pre-declared for you in const.h.
 * You must use those variables, rather than declaring your own.
 * IF YOU VIOLATE THIS RESTRICTION, YOU WILL GET A ZERO!
 *
 * IMPORTANT: You MAY NOT use floating point arithmetic or declare
 * any "float" or "double" variables.  IF YOU VIOLATE THIS RESTRICTION,
 * YOU WILL GET A ZERO!
 */


int string_to_int(char *s)
{
    int num = 0;
    while(*s != '\0')
    {
        if(*s >= '0' && *s <= '9')
        {
            //shifts digits to the left by one decimal place and add the current digit
            num = num *10 + *s - '0';
        }
        else
            return 0;
        ++s;
    }
    return num;
}
int compare_string(char *s1,char *s2)
{
    while(*s1 != '\0' || *s1 != '\0')
    {
        if(*s1 == *s2)
        {
            s1++;
            s2++;
        }
        else
            return 0;
    }
    return 1;
}

int build_huff()
{
    unsigned char *input_block = current_block;


    input_block = current_block;


    NODE *nodes_ptr = nodes;
   // printf("%p\n",nodes_ptr);
    int i;
    int found = 0;
    num_nodes = 0;

    while(*input_block != '\0')
    {
         NODE *nodes2_array = nodes;
        for(i = 0 ;i < num_nodes;i++)
        {
            if((unsigned char)nodes2_array->symbol == *input_block)
            {
                nodes2_array->weight = nodes2_array->weight + 1;
                //printf("executed");
                found = 1;
            }
            nodes2_array++;
        }
        //printf("%d\n",found);

        if(found != 1)
        {
            nodes_ptr->symbol = (short)*input_block;
            nodes_ptr->weight = 1;
            nodes_ptr->parent = NULL;
            nodes_ptr->right = NULL;
            nodes_ptr->left = NULL;
            //printf("%c %d\n",(unsigned char)nodes_ptr->symbol,nodes_ptr->weight);
            num_nodes = num_nodes + 1;

            nodes_ptr++;

        }
        input_block++;
        found = 0;
    }
    // adding the end block symbol
    nodes_ptr->symbol = 400;
    nodes_ptr->weight = 0;
    nodes_ptr->parent = NULL;
    nodes_ptr->right = NULL;
    nodes_ptr->left = NULL;
    num_nodes = num_nodes + 1;
    //testing if leaf nodes created


    //leaf nodes are now in the array, now remove the 2 min nodes and replace with parent - the sum of the two removed nodes
    int num_leaf = num_nodes;
    num_nodes = (2*num_nodes)-1;

    while(num_leaf != 1)
    {

        NODE *min_node;
        NODE *min_node2;

         nodes_ptr = nodes;

        for(i = 0; i < num_leaf && num_leaf != 1; i++)
        {
            if(i == 0)
            {
                min_node = nodes;
            }
            else if(i == 1)
            {
                if(min_node->weight > nodes_ptr->weight)
                {
                    min_node2 = min_node;
                    min_node = nodes_ptr;
                }
                else
                {
                    min_node2 = nodes_ptr;
                }
            }
            else
            {
                if(min_node->weight > nodes_ptr->weight && min_node2->weight > nodes_ptr->weight)
                {
                    min_node2 = min_node;
                    min_node = nodes_ptr;
                }
                else if(min_node2->weight > nodes_ptr->weight)
                {
                    min_node2 = nodes_ptr;
                }
            }
            nodes_ptr++;
        }


        NODE min;
        min.symbol = min_node->symbol;
        min.weight = min_node->weight;
        //min.parent = min_node->parent;
        min.left = min_node->left;
        min.right = min_node->right;
        NODE min2;
        min2.symbol = min_node2->symbol;
        min2.weight = min_node2->weight;
        //min2.parent = min_node2->parent;
        min2.left = min_node2->left;
        min2.right = min_node2->right;


        nodes_ptr = nodes;
        NODE *next = ++nodes_ptr;
        nodes_ptr = nodes;

        int found = 0;

        for(i = 0; i < num_leaf;i++)
        {

            if(nodes_ptr->symbol == min.symbol || found == 1)
            {
                nodes_ptr->weight = next->weight;
                nodes_ptr->symbol = next->symbol;
                nodes_ptr->left = next->left;
                nodes_ptr->right = next->right;
                nodes_ptr->parent = next->parent;
                found = 1;
            }
            nodes_ptr++;
            next++;
        }


        nodes_ptr = nodes;
        next = ++nodes_ptr;
        nodes_ptr = nodes;

        found = 0;
        for(i = 0; i < num_leaf-1;i++)
        {

            if(nodes_ptr->symbol == min2.symbol || found == 1)
            {
                nodes_ptr->weight = next->weight;
                nodes_ptr->symbol = next->symbol;
                nodes_ptr->left = next->left;
                nodes_ptr->right = next->right;
                nodes_ptr->parent = next->parent;
                found = 1;
            }
            nodes_ptr++;
            next++;
        }


        nodes_ptr = nodes;
        for(i = 0; i < 2*num_leaf-1;i++)
        {
            NODE *parent_index;
            if(i == 2*num_leaf-3)
            {
                //nodes_ptr = min_node2;
                nodes_ptr->weight = min2.weight;
                nodes_ptr->symbol = min2.symbol;
                nodes_ptr->parent = parent_index;
                nodes_ptr->left = min2.left;
                nodes_ptr->right = min2.right;
                //update parent left and right pointers
                parent_index->right = nodes_ptr;
            }
            else if(i == 2*num_leaf-2)
            {
                //nodes_ptr = min_node;
                nodes_ptr->weight = min.weight;
                nodes_ptr->symbol = min.symbol;
                nodes_ptr->left = min.left;
                nodes_ptr->right = min.right;
                nodes_ptr->parent = parent_index;
                //update parent left and right pointers
                parent_index->left = nodes_ptr;
            }
            else if(i == num_leaf-2)
            {
                nodes_ptr->symbol = 500;
                nodes_ptr->weight = min2.weight + min.weight;
                nodes_ptr->parent = NULL;

                parent_index = nodes_ptr;

            }
            nodes_ptr++;
        }

        num_leaf = num_leaf-1;
    }

    NODE *nodes_array = nodes;
    NODE **node_symbol = node_for_symbol;
    for(i = 0 ;i < num_nodes;i++)
    {
        //printf("%c %d %s\n",(unsigned char)nodes_array->symbol,nodes_array->weight, "is the current node");

        if(nodes_array->left == NULL && nodes_array->right == NULL)
        {
            //leaf node - assign pointer!
            *node_symbol++ = nodes_array;
            //node_symbol++;
        }

        if(nodes_array->left != NULL)
        {
            NODE *p = nodes_array->left;
            p->parent = nodes_array;
            //printf("%c %d %s\n",(unsigned char)p->symbol,p->weight,"is the left child");
        }
        if(nodes_array->right != NULL)
        {
            NODE *p = nodes_array->right;
            p->parent = nodes_array;
            //printf("%c %d %s\n\n",(unsigned char)p->symbol,p->weight,"is the right child");
        //printf("%d\n",nodes_array->symbol);
        }
/*
        if(nodes_array->parent != NULL)
        {
            NODE *p = nodes_array->parent;
            //printf("%c %d %s\n\n",(unsigned char)p->symbol,p->weight,"is the parent");
        }
        */
        nodes_array++;
    }
    num_leaf = (num_nodes+1)/2;
    node_symbol = node_for_symbol;
    for(i = 0; i <num_leaf;i++)
    {
        NODE *node_p = *node_symbol;
        printf("%c %d %s\n\n",node_p->symbol,node_p->weight," is the leaf node");
        node_symbol++;
    }
    printf("\n");



    return 1;
}

/**
 * @brief Emits a description of the Huffman tree used to compress the current block.
 * @details This function emits, to the standard output, a description of the
 * Huffman tree used to compress the current block.  Refer to the assignment handout
 * for a detailed specification of the format of this description.
 */
void emit_huffman_tree() {
    // To be implemented.
}

/**
 * @brief Reads a description of a Huffman tree and reconstructs the tree from
 * the description.
 * @details  This function reads, from the standard input, the description of a
 * Huffman tree in the format produced by emit_huffman_tree(), and it reconstructs
 * the tree from the description.  Refer to the assignment handout for a specification
 * of the format for this description, and a discussion of how the tree can be
 * reconstructed from it.
 *
 * @return 0 if the tree is read and reconstructed without error, otherwise 1
 * if an error occurs.
 */
int read_huffman_tree() {
    // To be implemented.
    return 1;
}

/**
 * @brief Reads one block of data from standard input and emits corresponding
 * compressed data to standard output.
 * @details This function reads raw binary data bytes from the standard input
 * until the specified block size has been read or until EOF is reached.
 * It then applies a data compression algorithm to the block and outputs the
 * compressed block to the standard output.  The block size parameter is
 * obtained from the global_options variable.
 *
 * @return 0 if compression completes without error, 1 if an error occurs.
 */
int compress_block() {
    // To be implemented.
    return 1;
}

/**
 * @brief Reads one block of compressed data from standard input and writes
 * the corresponding uncompressed data to standard output.
 * @details This function reads one block of compressed data from the standard
 * inputk it decompresses the block, and it outputs the uncompressed data to
 * the standard output.  The input data blocks are assumed to be in the format
 * produced by compress().  If EOF is encountered before a complete block has
 * been read, it is an error.
 *
 * @return 0 if decompression completes without error, 1 if an error occurs.
 */
int decompress_block() {
    // To be implemented.
    return 1;
}

/**
 * @brief Reads raw data from standard input, writes compressed data to
 * standard output.
 * @details This function reads raw binary data bytes from the standard input in
 * blocks of up to a specified maximum number of bytes or until EOF is reached,
 * it applies a data compression algorithm to each block, and it outputs the
 * compressed blocks to standard output.  The block size parameter is obtained
 * from the global_options variable.
 *
 * @return 0 if compression completes without error, 1 if an error occurs.
 */
int compress()
{
    int i = 0;
    int c;
    unsigned char *input_block = current_block;
    //printf("%d %s\n",global_options, "is the global_options");
    unsigned int blocksize = global_options - 0x2;
    //printf("%d %s\n",blocksize, "is the blocksize");
    blocksize = (blocksize >> 16) + 1;
    //printf("%d %s\n",blocksize, "is the blocksize");


    //no input
    if( (c = getchar()) == EOF)
        return 1;
    do
    {
        *input_block = (unsigned char)c;
        //printf("%c\n",(unsigned char)c);
        if((i+1) == blocksize)
        {
            //printf("%d %s\n",blocksize, "is the max");
            build_huff();
            i = 0; //reset the counter
            input_block = current_block;
        }
        else
        {
            i++;
            input_block++;
        }
    }while( (c = getchar()) != EOF);

    // partial block read in due to end of input
    // set the end of the block NULL to indicate where to stop reading input
    if(i != blocksize && i != 0)
    {
        //printf("%d %d\n",blocksize,i);
        *input_block = '\0';
        build_huff();
    }

    // testing if input was processed correctly from stdin
    //input_block = current_block;
    //printf("executed\n");
    /*
    while(*input_block != '\0')
    {
        printf("%c",*input_block);
        input_block++;
    }
    printf("\n");
    */

    return 0;

}

/**
 * @brief Reads compressed data from standard input, writes uncompressed
 * data to standard output.
 * @details This function reads blocks of compressed data from the standard
 * input until EOF is reached, it decompresses each block, and it outputs
 * the uncompressed data to the standard output.  The input data blocks
 * are assumed to be in the format produced by compress().
 *
 * @return 0 if decompression completes without error, 1 if an error occurs.
 */
int decompress() {
    // To be implemented.
    return 1;
}

/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the
 * program, returning 0 if validation succeeds and 1 if validation fails.
 * Upon successful return, the selected program options will be set in the
 * global variable "global_options", where they will be accessible
 * elsewhere in the program.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 0 if validation succeeds and 1 if validation fails.
 * Refer to the homework document for the effects of this function on
 * global variables.
 * @modifies global variable "global_options" to contain a bitmap representing
 * the selected options.
 */
int validargs(int argc, char **argv)
{
    if(argc == 1)
    {
          // no flags are provided display usage and return with an EXIT_FALIURE
         return 1;
    }
    else
    {
        char *first_arg = *++argv;

        if(compare_string(first_arg,"-h"))
        {
            //least significant bit is 1
            global_options =0x1;
            return 0;
        }
        else if(compare_string(first_arg,"-c"))
        {
            //perform data compression
            if(argc == 2)
            {
                //second-least significant bit is 1
                global_options =0xffff0002;
                //printf("%lu %s\n",(long unsigned)global_options,"executed2");
                return 0;
            }
            else if(argc == 4)
            {
                char *second_arg = *++argv;

                if(compare_string(second_arg,"-b"))
                {
                    char *third_arg = *++argv;
                    int block_num = string_to_int(third_arg)-1;

                    if(block_num+1 <= MAX_BLOCK_SIZE && block_num+1 >= MIN_BLOCK_SIZE)
                    {
                        //second least significant bit is blocksize -1 in the 16
                        //most significant bit of global_options
                        //global_options = 0xffff0004;
                        //printf("%d\n",block_num);
                        block_num = block_num << 16;
                        global_options = 0x2;
                        global_options = block_num | global_options;
                        //printf("%d\n",block_num);
                        //printf("%lu %s\n",(long unsigned)global_options,"executed3");
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 1;
            }

        }
        else if(compare_string(first_arg,"-d"))
        {
            if(argc != 2)
            {
                return 1; //invalid additional arguments
            }
            else
            {
                //third-most significant bit is 1 for decompression
                global_options =  0xffff0004;
                return 0; //valid
            }
        }
        else
        {
            return 1;
        }
    }
}



