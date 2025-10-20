#include "../../include/server.h"


char* return_code(int status_code, char* file) 
{
    char* code_definition = NULL;
    char* sent_file = NULL;
    sent_file_getter(&status_code, &code_definition, &sent_file);

    const char* content_type = content_type_getter(file);

    int content_length = strlen(sent_file); // size of thing we are sending


    char *response = malloc(1096);
    sprintf(
        response,
        "HTTP/1.1 %i %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %i\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status_code, code_definition, content_type, content_length, sent_file);

    return response;
}

char* content_type_getter(char* file) 
{
    //format is category/type  ex. text/html image/gif
    char* dot_search = strrchr(file, '.'); // dot_search = pointer to last occurence of '.'
    const char* file_type; 
    if (dot_search != NULL) 
    {
        file_type = dot_search + 1; // right after the dot
    }
    
    else 
    {
        file_type = "none";
    }
    // used https://www.iana.org/assignments/media-types/media-types.xhtml as reference
    char text_list[2][12] = {"html", "javascript"}; // first value = how many names (according to website) to include, 2nd value = length of names (which should be much longer but not relevant)
    char image_list[2][4] = {"png", "gif"};
    const char* file_category = "none";

    for (int i = 0; i < 2; i++) 
    {
        if (!strcmp(text_list[i], file_type)) 
        {
            file_category = "text";
        }

        else if (!strcmp(image_list[i], file_type)) 
        {
            file_category = "image";
        }

    }

    char* content_type = malloc(100);
    sprintf(content_type, "%s/%s", file_category, file_type);
    return content_type;
}

void sent_file_getter(int* status_code, char** code_definition, char** sent_file) 
{
    switch (*status_code)
    {
        case 200:
            *code_definition = "Success";
            *sent_file = "<html><body><h1>200 Success</h1></body></html>";
            break;

        case 404:
            *code_definition = "Not Found";
            *sent_file = "<html><body><h1>404 Not Found</h1><p>Resource not found on server.</p></body></html>";
            break;
        
        default:
            *code_definition = "Internal Server Error";
            *status_code = 500;
            *sent_file = "<html><body><h1>500 Internal Sever Error</h1></body></html>";
            break;
    }
}