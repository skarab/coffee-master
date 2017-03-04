function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6272\" class=\"headerLeftMenuInActive\"><a id=\"aID6272\" href=\"#\" OnMouseOver=\"link('_dir','vector0',this)\" class=\"leftMenuLinkHeadInActive\">vector</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID732\" class=\"leftMenuInActive\"><a id=\"aID732\" href=\"#\" OnMouseOver=\"link('_class','Vector6216',this)\" class=\"leftMenuLinkInActive\">Vector<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1130\" class=\"leftMenuInActive\"><a id=\"aID1130\" href=\"#\" OnMouseOver=\"link('_member','Vector7578827',this)\" class=\"leftMenuLinkInActive\">Vector</a></div>\n");
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
