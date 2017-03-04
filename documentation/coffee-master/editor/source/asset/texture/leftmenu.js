function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6474\" class=\"headerLeftMenuInActive\"><a id=\"aID6474\" href=\"#\" OnMouseOver=\"link('_dir','texture0',this)\" class=\"leftMenuLinkHeadInActive\">texture</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1068\" class=\"leftMenuInActive\"><a id=\"aID1068\" href=\"#\" OnMouseOver=\"link('_class','Texture22463',this)\" class=\"leftMenuLinkInActive\">Texture</a></div>\n");
document.write("<div id=\"divID1069\" class=\"leftMenuInActive\"><a id=\"aID1069\" href=\"#\" OnMouseOver=\"link('_class','TextureHDR22463',this)\" class=\"leftMenuLinkInActive\">TextureHDR</a></div>\n");
document.write("<div id=\"divID1070\" class=\"leftMenuInActive\"><a id=\"aID1070\" href=\"#\" OnMouseOver=\"link('_class','TextureIES22463',this)\" class=\"leftMenuLinkInActive\">TextureIES</a></div>\n");
document.write("<div id=\"divID1071\" class=\"leftMenuInActive\"><a id=\"aID1071\" href=\"#\" OnMouseOver=\"link('_class','TexturePNG22463',this)\" class=\"leftMenuLinkInActive\">TexturePNG</a></div>\n");
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
