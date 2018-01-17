/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef __HTTPD_H__
#define __HTTPD_H__


typedef enum file_type_enum
{
  HTML, /* .htm(l) */
  GIF, /* .gif */
  PNG, /* .png */ 
  JPEG, /* .jp(e)g */
  OCTET_STREAM, /* .bin, .class, ??? */
  REALAUDIO, /* .ra(m) */
  TEXT, /* .txt */
  JAVASCRIPT, /* .js */
  CSS /* .css */
}
CONTENT_TYPE;
/*
static const char *httpContentType_header[] = {
  "Content-Type: text/html\r\n",
  "Content-Type: image/gif\r\n",
  "Content-Type: image/png\r\n",
  "Content-Type: image/jpeg\r\n",
  "Content-Type: application/octet-stream\r\n",
  "Content-Type: audio/x-pn-realaudio\r\n",
  "Content-Type: text/plain\r\n",
  "Content-Type: application/x-javascript\r\n",
  "Content-Type: text/css\r\n",
  (void *)0
};
*/
typedef enum getResponseEnum
{
  HTTP_200_OK,
  HTTP_404_NOT_FOUND
} HTTP_RESPONSE;
/*
static const char *httpResponseText_1_0[] = {
  "HTTP/1.0 200 OK\r\n",
  "HTTP/1.0 404 File not found\r\n"
};
static const char *httpResponseText_1_1[] = {
  "HTTP/1.1 200 OK\r\n",
  "HTTP/1.1 404 File not found\r\n"
};
static const char *httpContentLength = "Content-Length: ";
static const char *httpConnectionClose = "Connection: close\r\n";
*/

void httpd_init(void);

/*
 * Function pointer for a CGI script handler.
 *
 * This function is called each time the HTTPD server is asked for a file
 * whose name was previously registered as a CGI function using a call to
 * http_set_cgi_handler. The iIndex parameter provides the index of the
 * CGI within the ppcURLs array passed to http_set_cgi_handler. Parameters
 * pcParam and pcValue provide access to the parameters provided along with
 * the URI. iNumParams provides a count of the entries in the pcParam and
 * pcValue arrays. Each entry in the pcParam array contains the name of a
 * parameter with the corresponding entry in the pcValue array containing the
 * value for that parameter. Note that pcParam may contain multiple elements
 * with the same name if, for example, a multi-selection list control is used
 * in the form generating the data.
 *
 * The function should return a pointer to a character string which is the
 * path and filename of the response that is to be sent to the connected
 * browser, for example "/thanks.htm" or "/response/error.ssi".
 *
 * The maximum number of parameters that will be passed to this function via
 * iNumParams is defined by MAX_CGI_PARAMETERS. Any parameters in the incoming
 * HTTP request above this number will be discarded.
 *
 * Requests intended for use by this CGI mechanism must be sent using the GET
 * method (which encodes all parameters within the URI rather than in a block
 * later in the request). Attempts to use the POST method will result in the
 * request being ignored.
 *
 */
typedef char *(*tCGIHandler)(char *pcValue);
/*
 * Structure defining the base filename (URL) of a CGI and the associated
 * function which is to be called when that URL is requested.
 */
typedef struct
{
    const char *pcCGIName;
    tCGIHandler pfnCGIHandler;
} tCGI;

void http_set_cgi_handlers(const tCGI *pCGIs, int iNumHandlers);

#define MAX_CGI_PARAMETERS 16

#endif /* __HTTPD_H__ */
