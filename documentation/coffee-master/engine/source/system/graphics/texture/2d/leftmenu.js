function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6383\" class=\"headerLeftMenuInActive\"><a id=\"aID6383\" href=\"#\" OnMouseOver=\"link('_dir','2d0',this)\" class=\"leftMenuLinkHeadInActive\">2d</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID893\" class=\"leftMenuInActive\"><a id=\"aID893\" href=\"#\" OnMouseOver=\"link('_class','Texture2D54809',this)\" class=\"leftMenuLinkInActive\">Texture2D</a></div>\n");
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
