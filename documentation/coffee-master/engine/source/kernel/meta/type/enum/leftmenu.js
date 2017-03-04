function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6312\" class=\"headerLeftMenuInActive\"><a id=\"aID6312\" href=\"#\" OnMouseOver=\"link('_dir','enum0',this)\" class=\"leftMenuLinkHeadInActive\">enum</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID793\" class=\"leftMenuInActive\"><a id=\"aID793\" href=\"#\" OnMouseOver=\"link('_class','Enum53261',this)\" class=\"leftMenuLinkInActive\">Enum</a></div>\n");
document.write("<div id=\"divID794\" class=\"leftMenuInActive\"><a id=\"aID794\" href=\"#\" OnMouseOver=\"link('_class','EnumValue53261',this)\" class=\"leftMenuLinkInActive\">EnumValue</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6215\" class=\"leftMenuInActive\"><a id=\"aID6215\" href=\"#\" OnMouseOver=\"link('_member','ENUM_TYPE240823',this)\" class=\"leftMenuLinkInActive\">ENUM_TYPE</a></div>\n");
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
