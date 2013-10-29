%{

/* from lexer.l - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdio.h>
#include "../headers/vectors.h"
#include "grammar.h"

int linenum = 1;
%}
%%
-?[0-9]+(\.[0-9]+)?       { yylval.dValue = atof(yytext); return FLOAT; };
include\s\"[^\"]\" {
  printf("Got include file %s\n", yytext);
}
<<EOF>> {
          yypop_buffer_state();
     
          if ( !YY_CURRENT_BUFFER )
          {
            yyterminate();
          }
        }
camera                  return TOK_CAMERA;
\{                      return OPEN_CURLIES;
\}                      return CLOSE_CURLIES;
\(                      return OPENBRACKET;
\)                      return TOK_CLOSEBRACKET;
at                      return TOK_AT;
ambient                 return AMBIENT;
center                  return CENTER;
colour                  return COLOUR;
depth                   return TOK_DEPTH;
diffuse                 return DIFFUSE;
directional             return DIRECTIONAL;
down                    return TOK_DOWN;
height                  return TOK_HEIGHT;
look-at                 return TOK_LOOKAT;
light                   return LIGHT;
material                return MATERIAL;
normal                  return NORMAL;
object                  return OBJECT;
plane                   return PLANE;
box											return BOX;
point                   return POINT;
position                return POSITION;
radius                  return RADIUS;
resolution              return TOK_RESOLUTION;
sphere                  return SPHERE;
width                   return TOK_WIDTH;
a 											return BOXA;
b                       return BOXB;
\n                      linenum++;
[ \t]+                  /* ignore whitespace */;
\/\/.*                  /* ignore comments */;
%%
