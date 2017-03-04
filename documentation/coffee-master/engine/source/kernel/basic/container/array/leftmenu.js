function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6267\" class=\"headerLeftMenuInActive\"><a id=\"aID6267\" href=\"#\" OnMouseOver=\"link('_dir','array0',this)\" class=\"leftMenuLinkHeadInActive\">array</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID726\" class=\"leftMenuInActive\"><a id=\"aID726\" href=\"#\" OnMouseOver=\"link('_class','Array6216',this)\" class=\"leftMenuLinkInActive\">Array<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1124\" class=\"leftMenuInActive\"><a id=\"aID1124\" href=\"#\" OnMouseOver=\"link('_member','Array7578827',this)\" class=\"leftMenuLinkInActive\">Array</a></div>\n");
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
