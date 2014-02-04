// send the XML file DATA status
void XML_response(EthernetClient cl)
{
    int modelNumber = 0;
    
    Serial.println("XML_response");
    Serial.print("powerState ");
    Serial.println(powerState);
    cl.println("<?xml version = \"1.0\" ?>");
    cl.println("<outputs>");

    cl.print("<power>");
      cl.print(powerState);
    cl.println("</power>");

    cl.print("<degree10>");
      cl.print(degree10State);
    cl.println("</degree10>");

    cl.print("<degree30>");
      cl.print(degree30State);
    cl.println("</degree30>");
 
    cl.print("<degree45>");
      cl.print(degree45State);
    cl.println("</degree45>");
 
    cl.print("<degree60>");
      cl.print(degree60State);
    cl.println("</degree60>");
    
    cl.print("<degree130>");
      cl.print(degree130State);
    cl.println("</degree130>");
    
    cl.println("</outputs>");
}

// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++) {
        str[i] = 0;
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }

    return 0;
}
