function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6502\" class=\"headerLeftMenuInActive\"><a id=\"aID6502\" href=\"#\" OnMouseOver=\"link('_dir','hierarchy0',this)\" class=\"leftMenuLinkHeadInActive\">hierarchy</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6281\" class=\"leftMenuInActive\"><a id=\"aID6281\" href=\"#\" OnMouseOver=\"link('_dir','tree/tree0',this)\" class=\"leftMenuLinkInActive\">tree</a></div>\n");
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
