function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6283\" class=\"headerLeftMenuInActive\"><a id=\"aID6283\" href=\"#\" OnMouseOver=\"link('_dir','curve0',this)\" class=\"leftMenuLinkHeadInActive\">curve</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID743\" class=\"leftMenuInActive\"><a id=\"aID743\" href=\"#\" OnMouseOver=\"link('_class','Bezier6216',this)\" class=\"leftMenuLinkInActive\">Bezier<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1163\" class=\"leftMenuInActive\"><a id=\"aID1163\" href=\"#\" OnMouseOver=\"link('_member','Bezier7578827',this)\" class=\"leftMenuLinkInActive\">Bezier</a></div>\n");
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
