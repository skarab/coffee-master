function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6432\" class=\"headerLeftMenuInActive\"><a id=\"aID6432\" href=\"#\" OnMouseOver=\"link('_dir','macros0',this)\" class=\"leftMenuLinkHeadInActive\">macros</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Macros</div>\n");
document.write("<div id=\"divID686\" class=\"leftMenuInActive\"><a id=\"aID686\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_PropertyInterface706623580',this)\" class=\"leftMenuLinkInActive\">COFFEE_PropertyInterface</a></div>\n");
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
