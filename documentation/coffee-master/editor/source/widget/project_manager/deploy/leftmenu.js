function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6494\" class=\"headerLeftMenuInActive\"><a id=\"aID6494\" href=\"#\" OnMouseOver=\"link('_dir','deploy0',this)\" class=\"leftMenuLinkHeadInActive\">deploy</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1106\" class=\"leftMenuInActive\"><a id=\"aID1106\" href=\"#\" OnMouseOver=\"link('_class','DeployDesktop22483',this)\" class=\"leftMenuLinkInActive\">DeployDesktop</a></div>\n");
document.write("<div id=\"divID1107\" class=\"leftMenuInActive\"><a id=\"aID1107\" href=\"#\" OnMouseOver=\"link('_class','DeployPackage22483',this)\" class=\"leftMenuLinkInActive\">DeployPackage</a></div>\n");
document.write("<div id=\"divID1108\" class=\"leftMenuInActive\"><a id=\"aID1108\" href=\"#\" OnMouseOver=\"link('_class','DeployTarget22483',this)\" class=\"leftMenuLinkInActive\">DeployTarget</a></div>\n");
document.write("<div id=\"divID6181\" class=\"leftMenuInActive\"><a id=\"aID6181\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
