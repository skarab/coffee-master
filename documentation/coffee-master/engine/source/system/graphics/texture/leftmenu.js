function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6385\" class=\"headerLeftMenuInActive\"><a id=\"aID6385\" href=\"#\" OnMouseOver=\"link('_dir','texture0',this)\" class=\"leftMenuLinkHeadInActive\">texture</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6383\" class=\"leftMenuInActive\"><a id=\"aID6383\" href=\"#\" OnMouseOver=\"link('_dir','2d/2d0',this)\" class=\"leftMenuLinkInActive\">2d</a></div>\n");
document.write("<div id=\"divID6384\" class=\"leftMenuInActive\"><a id=\"aID6384\" href=\"#\" OnMouseOver=\"link('_dir','array/array0',this)\" class=\"leftMenuLinkInActive\">array</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID895\" class=\"leftMenuInActive\"><a id=\"aID895\" href=\"#\" OnMouseOver=\"link('_class','Texture54809',this)\" class=\"leftMenuLinkInActive\">Texture</a></div>\n");
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
