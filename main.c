#include <stdio.h>
#include "lwcrypt.h"
#include "lwbase64.h"
#include "config/config.h"
#include "config/iniparser.h"


void test_base64(char *text)
{
    char encoded[255], decoded[255];
    size_t text_size = strlen(text);


    base64encode(text, text_size, encoded, 255);

    size_t enc_size = strlen(encoded);
    base64decode(encoded, enc_size, decoded, &text_size);

    printf("Base64: %s\nDecoded: %s\n", encoded, decoded);

}


void test_config()
{
    lwConfig lwc;
    lwconf_init(&lwc);
    lwConfigItem *root = lwc.globalNamespace;
    lwconf_set(root,"ahoj", "svet");
    lwconf_set(root, "name", "Peter");
    lwconf_set(root, "email", "123456");
    lwConfigItem *name = lwconf_item_get(root, "name");
    lwconf_set(name, "surname", "Lologon");

    lwconf_print_subtree(root);

    lwconf_destroy(&lwc);
}


void test_ini_parser()
{
    lwConfig lwc;
    lwconf_init(&lwc);
    int res = lwpars_ini_load("test.ini", &lwc);
    printf("Return code: %d", res);
    lwconf_print_subtree(lwc.globalNamespace);
    lwconf_destroy(&lwc);
}



void enc_test()
{
    printf("Hello World!\n");
    char * text = "Ahoj svetlo, ako sa mas ?";
    char * key = "SomeRandomKey";
    char result[256];
    char decoded[256];
    memset(result, 0, 255);
    memset(decoded, 0, 255);
    int textSize = strlen(text);
    int keySize = strlen(key);

    lwcrypt_simple_xor(text, key, result, textSize, keySize);
    lwcrypt_simple_xor(result, key, decoded, textSize, keySize);
    printf("Original text: %s\nEncryptedText: %s\n", text, result);
    printf("Decrypted text: %s\n ", decoded);

    test_base64(text);
}



int main(void)
{
    test_ini_parser();

    return 0;
}

