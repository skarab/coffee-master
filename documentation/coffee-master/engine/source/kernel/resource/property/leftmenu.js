function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6322\" class=\"headerLeftMenuInActive\"><a id=\"aID6322\" href=\"#\" OnMouseOver=\"link('_dir','property0',this)\" class=\"leftMenuLinkHeadInActive\">property</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID804\" class=\"leftMenuInActive\"><a id=\"aID804\" href=\"#\" OnMouseOver=\"link('_class','Property24673',this)\" class=\"leftMenuLinkInActive\">Property<></a></div>\n");
document.write("<div id=\"divID805\" class=\"leftMenuInActive\"><a id=\"aID805\" href=\"#\" OnMouseOver=\"link('_class','PropertyBase24579',this)\" class=\"leftMenuLinkInActive\">PropertyBase</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1285\" class=\"leftMenuInActive\"><a id=\"aID1285\" href=\"#\" OnMouseOver=\"link('_member','Property812731585',this)\" class=\"leftMenuLinkInActive\">Property</a></div>\n");
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
