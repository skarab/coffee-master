function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6496\" class=\"headerLeftMenuInActive\"><a id=\"aID6496\" href=\"#\" OnMouseOver=\"link('_dir','properties0',this)\" class=\"leftMenuLinkHeadInActive\">properties</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID6170\" class=\"leftMenuInActive\"><a id=\"aID6170\" href=\"#\" OnMouseOver=\"link('_class','Dialog0',this)\" class=\"leftMenuLinkInActive\">Dialog</a></div>\n");
document.write("<div id=\"divID1112\" class=\"leftMenuInActive\"><a id=\"aID1112\" href=\"#\" OnMouseOver=\"link('_class','Properties22483',this)\" class=\"leftMenuLinkInActive\">Properties</a></div>\n");
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
