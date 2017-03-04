function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6429\" class=\"headerLeftMenuInActive\"><a id=\"aID6429\" href=\"#\" OnMouseOver=\"link('_dir','property_window0',this)\" class=\"leftMenuLinkHeadInActive\">property_window</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID962\" class=\"leftMenuInActive\"><a id=\"aID962\" href=\"#\" OnMouseOver=\"link('_class','PropertyWindow49249',this)\" class=\"leftMenuLinkInActive\">PropertyWindow</a></div>\n");
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
