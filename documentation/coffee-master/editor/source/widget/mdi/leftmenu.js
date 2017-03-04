function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6489\" class=\"headerLeftMenuInActive\"><a id=\"aID6489\" href=\"#\" OnMouseOver=\"link('_dir','mdi0',this)\" class=\"leftMenuLinkHeadInActive\">mdi</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1099\" class=\"leftMenuInActive\"><a id=\"aID1099\" href=\"#\" OnMouseOver=\"link('_class','MDI22483',this)\" class=\"leftMenuLinkInActive\">MDI</a></div>\n");
document.write("<div id=\"divID6196\" class=\"leftMenuInActive\"><a id=\"aID6196\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
