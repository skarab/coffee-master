function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6297\" class=\"headerLeftMenuInActive\"><a id=\"aID6297\" href=\"#\" OnMouseOver=\"link('_dir','macros0',this)\" class=\"leftMenuLinkHeadInActive\">macros</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Macros</div>\n");
document.write("<div id=\"divID573\" class=\"leftMenuInActive\"><a id=\"aID573\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Assert2110149038',this)\" class=\"leftMenuLinkInActive\">COFFEE_Assert</a></div>\n");
document.write("<div id=\"divID577\" class=\"leftMenuInActive\"><a id=\"aID577\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_CreateSingleton1886521613',this)\" class=\"leftMenuLinkInActive\">COFFEE_CreateSingleton</a></div>\n");
document.write("<div id=\"divID575\" class=\"leftMenuInActive\"><a id=\"aID575\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_DeclareSingleton640163014',this)\" class=\"leftMenuLinkInActive\">COFFEE_DeclareSingleton</a></div>\n");
document.write("<div id=\"divID578\" class=\"leftMenuInActive\"><a id=\"aID578\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_DestroySingleton1886521613',this)\" class=\"leftMenuLinkInActive\">COFFEE_DestroySingleton</a></div>\n");
document.write("<div id=\"divID572\" class=\"leftMenuInActive\"><a id=\"aID572\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Error1869218870',this)\" class=\"leftMenuLinkInActive\">COFFEE_Error</a></div>\n");
document.write("<div id=\"divID576\" class=\"leftMenuInActive\"><a id=\"aID576\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_ImplementSingleton640163014',this)\" class=\"leftMenuLinkInActive\">COFFEE_ImplementSingleton</a></div>\n");
document.write("<div id=\"divID571\" class=\"leftMenuInActive\"><a id=\"aID571\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Warning2437918432',this)\" class=\"leftMenuLinkInActive\">COFFEE_Warning</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Defines</div>\n");
document.write("<div id=\"divID574\" class=\"leftMenuInActive\"><a id=\"aID574\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Log498113464',this)\" class=\"leftMenuLinkInActive\">COFFEE_Log</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
