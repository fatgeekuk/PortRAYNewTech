%{

/* from lexer.l - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdio.h>
#include "../headers/vectors.h"
#include "grammar.h"

int linenum = 1;
%}
%%
-?[0-9]+(\.[0-9]+)?       { yylval.dValue = atof(yytext); return FLOAT; };
camera                  return TOK_CAMERA;
\{                      return OPEN_CURLIES;
\}                      return CLOSE_CURLIES;
\(                      return OPENBRACKET;
\)                      return TOK_CLOSEBRACKET;
at                      return TOK_AT;
down                    return TOK_DOWN;
look-at                 return TOK_LOOKAT;
width                   return TOK_WIDTH;
height                  return TOK_HEIGHT;
depth                   return TOK_DEPTH;
resolution              return TOK_RESOLUTION;
light                   return LIGHT;
position                return POSITION;
colour                  return COLOUR;
object                  return OBJECT;
sphere                  return SPHERE;
plane                   return PLANE;
center                  return CENTER;
radius                  return RADIUS;
normal                  return NORMAL;
material                return MATERIAL;
diffuse                 return DIFFUSE;
\n                      linenum++;
[ \t]+                  /* ignore whitespace */;
\/\/.*                  /* ignore comments */;
%%
