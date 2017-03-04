function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6291\" class=\"headerLeftMenuInActive\"><a id=\"aID6291\" href=\"#\" OnMouseOver=\"link('_dir','color0',this)\" class=\"leftMenuLinkHeadInActive\">color</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID755\" class=\"leftMenuInActive\"><a id=\"aID755\" href=\"#\" OnMouseOver=\"link('_class','Color39014',this)\" class=\"leftMenuLinkInActive\">Color</a></div>\n");
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
