function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6351\" class=\"headerLeftMenuInActive\"><a id=\"aID6351\" href=\"#\" OnMouseOver=\"link('_dir','spot0',this)\" class=\"leftMenuLinkHeadInActive\">spot</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID853\" class=\"leftMenuInActive\"><a id=\"aID853\" href=\"#\" OnMouseOver=\"link('_class','ComponentLightSpot54809',this)\" class=\"leftMenuLinkInActive\">ComponentLightSpot</a></div>\n");
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
