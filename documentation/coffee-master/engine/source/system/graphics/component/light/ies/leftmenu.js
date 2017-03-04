function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6349\" class=\"headerLeftMenuInActive\"><a id=\"aID6349\" href=\"#\" OnMouseOver=\"link('_dir','ies0',this)\" class=\"leftMenuLinkHeadInActive\">ies</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID851\" class=\"leftMenuInActive\"><a id=\"aID851\" href=\"#\" OnMouseOver=\"link('_class','ComponentLightIES54809',this)\" class=\"leftMenuLinkInActive\">ComponentLightIES</a></div>\n");
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
