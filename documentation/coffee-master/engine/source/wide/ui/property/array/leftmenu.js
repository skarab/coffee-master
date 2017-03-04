function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6433\" class=\"headerLeftMenuInActive\"><a id=\"aID6433\" href=\"#\" OnMouseOver=\"link('_dir','array0',this)\" class=\"leftMenuLinkHeadInActive\">array</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID965\" class=\"leftMenuInActive\"><a id=\"aID965\" href=\"#\" OnMouseOver=\"link('_class','PropertyArray49249',this)\" class=\"leftMenuLinkInActive\">PropertyArray</a></div>\n");
document.write("<div id=\"divID966\" class=\"leftMenuInActive\"><a id=\"aID966\" href=\"#\" OnMouseOver=\"link('_class','PropertyArrayCombo49249',this)\" class=\"leftMenuLinkInActive\">PropertyArrayCombo</a></div>\n");
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
