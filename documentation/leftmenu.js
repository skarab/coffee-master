function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID0\" class=\"headerLeftMenuInActive\"><a id=\"aID0\" href=\"#\" OnMouseOver=\"link('','index',this)\" class=\"leftMenuLinkHeadInActive\">Documentation</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6475\" class=\"leftMenuInActive\"><a id=\"aID6475\" href=\"#\" OnMouseOver=\"link('_dir','coffee-master/editor/source/source0',this)\" class=\"leftMenuLinkInActive\">editor</a></div>\n");
document.write("<div id=\"divID6263\" class=\"leftMenuInActive\"><a id=\"aID6263\" href=\"#\" OnMouseOver=\"link('_dir','coffee-master/engine/source/source0',this)\" class=\"leftMenuLinkInActive\">engine</a></div>\n");
document.write("<div id=\"divID6500\" class=\"leftMenuInActive\"><a id=\"aID6500\" href=\"#\" OnMouseOver=\"link('_dir','coffee-master/player/source/source0',this)\" class=\"leftMenuLinkInActive\">player</a></div>\n");
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
