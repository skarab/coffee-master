function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6339\" class=\"headerLeftMenuInActive\"><a id=\"aID6339\" href=\"#\" OnMouseOver=\"link('_dir','component0',this)\" class=\"leftMenuLinkHeadInActive\">component</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6340\" class=\"leftMenuInActive\"><a id=\"aID6340\" href=\"#\" OnMouseOver=\"link('_dir','sound/sound0',this)\" class=\"leftMenuLinkInActive\">sound</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID840\" class=\"leftMenuInActive\"><a id=\"aID840\" href=\"#\" OnMouseOver=\"link('_class','Component45182',this)\" class=\"leftMenuLinkInActive\">Component</a></div>\n");
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
