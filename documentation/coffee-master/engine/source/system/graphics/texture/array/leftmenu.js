function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6384\" class=\"headerLeftMenuInActive\"><a id=\"aID6384\" href=\"#\" OnMouseOver=\"link('_dir','array0',this)\" class=\"leftMenuLinkHeadInActive\">array</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID894\" class=\"leftMenuInActive\"><a id=\"aID894\" href=\"#\" OnMouseOver=\"link('_class','TextureArray54809',this)\" class=\"leftMenuLinkInActive\">TextureArray</a></div>\n");
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
